#define _CRT_SECURE_NO_WARNINGS 1

#include"contact.h"
//通讯录
//1.保存1000个人的信息
//2.名字+性别+年龄+电话+住址
//3.增删查改 排序等
void menu() {
	printf("----------------------------\n");
	printf("*          THE MENU        *\n");
	printf("----------------------------\n");
	printf("*          1.add           *\n");
	printf("*          2.del           *\n");
	printf("*          3.search        *\n");
	printf("*          4.modify        *\n");
	printf("*          5.sort          *\n");
	printf("*          6.print         *\n");
	printf("*          0.exit          *\n");
	printf("----------------------------\n");
}
void _test() {
	int _input = 0;
	//创建通讯录
	Contact con;
	//初始化通讯录
	_initContact(&con);
	do {
		system("cls");
		menu();
		printf("there is %d PeoInfos in the Contact\n", con.sz);
		printf("----------------------------\n");
		printf("please choose:>");
		scanf("%d", &_input);
		switch (_input)
		{
		case ADD:
			_addContact(&con);
			break;
		case DEL:
			_delContact(&con);
			break;
		case SEARCH:
			_searchContact(&con);
			break;
		case MODIFY:
			_modifyContact(&con);
			break;
		case SORT:
			_sortByAge(&con);//按照年龄排序
			break;
		case PRINT:
			_printContact(&con);
			break;
		case EXIT:
			printf("exit contact\n");
			system("pause");
			exit(-1);
			break;
		default:
			printf("err\n");
			system("pause");
			break;
		}
	} while (_input);
}
int main() {
	_test();
	return 0;
}