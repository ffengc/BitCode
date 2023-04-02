# !/bin/bash

if 0;then
echo a{b,c,d}e  # abe ace ade 相当于{}里面就是一个分配
echo {z..a} # z y x w v u t s r q p o n m l k j i h g f e d c b a
echo {1..20} # 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
echo {1,2,3}{a,b,c} # 1a 1b 1c 2a 2b 2c 3a 3b 3c 相当于一个组合

# {} 也可以嵌套
echo a{b,{c,d}} # ab ac ad

# 如果有前导0，则bash4.0会视图让每个生成的量的位数都是相同的
echo {001..009} # 001 002 003 004 005 006 007 008 009

# alias
# 比较常用的
alias ll='ls -l'
# 打开当前目录下最后被修改的文件
alias Vim='vim 'ls -t | head -1''
# 找出当前目录下，5个最大的文件
alias findbig='find . -type f -exec ls -s {} \; | sort -n -r | head -5'
# 找出当前目录下所有的文件，包括隐藏文件，并加上颜色
alias ls='ls -aF --color=always'
# 清除全部历史命令记录和屏幕
alias hcl='history -c; clear'
# 查看磁盘空间使用情况
alias dus='df -h'


# 查看当前环境所所有的别名
alias
fi
