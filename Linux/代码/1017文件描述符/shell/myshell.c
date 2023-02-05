


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>


// shell运行原理: 通过让子进程执行命令，父进程等待和解析命令
// 为什么要子进程呢 -- 这样就算命令执行在子进程里面出错 -- 也不会影响父进程
// 因此我们不怕命令在命令行中出错
//


#define NUM 1024 // 定义一个大小为1024的缓冲区
char cmd_line[NUM]; //保存完整的命令行字符串
#define SIZE 32
char *g_argv[SIZE]; //保存拆分之后的命令行字符串

#define SEP " " //定义命令分隔符


#define INPUT_REDIR 1 //定义输入重定向
#define OUTPUT_REDIR 2 //定义输出重定向
#define APPEND_REDIR 3 //定义追加重定向
#define NONE_REDIR 0 //定义没有重定向

int redir_status = NONE_REDIR; //重定向类型

char* CheckRedir(char* start)
{
    assert(start);
    redir_status = NONE_REDIR;
    char* end = start + strlen(start)-1;//abcd\0
    //此时end是最后一个有效字符 -- 是\0的前一个
    while(end>=start)
    {
        if(*end == '>')
        {
            //ls -a -l>myfile.txt
            //ls -a -l>>myfile.txt
            //所以我们在前面要定义一下
            if(*(end-1) == '>')
            {
                //连续两个>  ----  追加重定向
                redir_status = APPEND_REDIR;
                *(end - 1) = '\0';
                end++;
                break;
            }
            //此时就是输出重定向
            *end = '\0';
            end++;
            redir_status = OUTPUT_REDIR;
            break;
        }
        else if(*end == '<')
        {
            //cat<myfile.txt 输入
            redir_status = INPUT_REDIR;
            *end = '\0';
            end++;
            break;
        }
        else
        {
            end--;
        }
    }
    if(end >= start)
    {
        //提前break的
        return end;//要打开的文件的地址
    }
    else
    {
        return NULL;
    }
}
int main()
{
    //获取全局的环境变量
    extern char** environ;


    //0. 命令行解释器，一定是一个常驻内存的进程 -- 不退出
    while(1)
    {
        //1. 打印出提示信息 [yufc@localhost myshell]# 
        //  其实这一串是可以用系统接口来获取的 -- 不过我们不关心这些
        printf("[yufc@localhost myshell]# ");
        fflush(stdout);//手动刷新
        
        //2. 获取用户的键盘输入[输入指的是各种指令和选项]
        // 要输入 -- 我们就要提供一个输入的缓冲区
        memset(cmd_line,'\0',sizeof cmd_line); //sizeof不是函数 -- 是运算符, 所以可以不用()
        if(fgets(cmd_line,sizeof cmd_line, stdin) == NULL)
        {
            //表示没有在stdin里面获取命令时出错
            continue;
        }
        //此时要把cmd_line最后面的回车去掉
        cmd_line[strlen(cmd_line)-1] = '\0';
        //printf("echo: %s\n",cmd_line);
        
        //3. 拆分命令
        //"ls -a -l" ---> "ls" "-a" "-l"
        //strtok
        //第一次调用 -- 要传入原始字符串
        //如果还要继续解析原字符串 -- 传入NULL

        //把重定向也添加进来
        //ls -a -l>log.txt     今天我们先不去处理空格 -- 空格是特殊处理
        //ls -a -l>>log.txt
        //ls -a -l<log.txt

        //分析是否有重定向
        //ls -a -l>log.txt  --->  ls -a -l\0log.txt

        char* sep = CheckRedir(cmd_line);
        // printf("%p\n",sep);

        g_argv[0] = strtok(cmd_line,SEP);
        int idx = 1;
        //可以把ls的颜色加一下
        if(strcmp(g_argv[0],"ls") == 0)
        {
            g_argv[idx++] = "--color=auto";
        }
        while(g_argv[idx++] = strtok(NULL,SEP)); //这种写法 -- 如果返回NULL，子串提取完成
        //测试一下看看提取的对不对
        //for(idx = 0;g_argv[idx];idx++)
        //{
        //    printf("g_argv[%d]: %s\n",idx,g_argv[idx]);
        //}
        
        //4. TODO
        if(strcmp(g_argv[0],"cd")==0)
        {
            //让父进程执行 -- 不要创建子进程
            //内置命令（内建命令） -- 本质就是shell中的一个函数调用
            //我们用一个系统调用 -- chdir
            if(g_argv[1]!=NULL)chdir(g_argv[1]);
            continue;
        }
        //导入环境变量
        // if(strcmp(g_argv[0],"export") == 0 && g_argv[1]!=NULL)
        // {
        //     int ret = putenv(g_argv[1]);
        //     if(ret == 0) printf("%s export success\n",g_argv[1]);
        //     continue;
        // }

        //5. fork()
        pid_t id = fork();
        printf("开始重定向2 %d\n",id);
        if(id == 0) //child
        {
            if(sep != NULL)
            {
                int fd = -1;
                //说明命令曾经有重定向
                switch(redir_status)
                {
                    case INPUT_REDIR:
                        fd = open(sep, O_RDONLY);
                        dup2(fd, 0);
                        break;
                    case OUTPUT_REDIR:
                        fd = open(sep, O_WRONLY | O_TRUNC | O_CREAT, 0666);
                        dup2(fd, 1);
                        break;
                    case APPEND_REDIR:
                        //TODO
                        fd = open(sep, O_WRONLY | O_APPEND | O_CREAT, 0666);
                        dup2(fd, 1);
                        break;
                    default:
                        printf("bug?\n");
                        break;
                }
            }
           // printf("下面功能让子进程进行的\n");
           // printf("child, MYVAL: %s\n", getenv("MYVAL"));
           // printf("child, PATH: %s\n", getenv("PATH"));
            //cd cmd , current child path
            //execvpe(g_argv[0], g_argv, environ); // ls -a -l -i
            //不是说好的程序替换会替换代码和数据吗？？
            //环境变量相关的数据，会被替换吗？？没有！
            execvp(g_argv[0], g_argv); // ls -a -l -i
            exit(1);
        }
        //父进程 -- 这里我们不用else了 -- 子进程执行完直接退出, 后面的肯定是父进程了
        int status = 0;
        pid_t ret = waitpid(id,&status,0);
        if(ret > 0)
        {
            printf("exit code: %d\n",WEXITSTATUS(status));
        }
    }
    return 0;
}
