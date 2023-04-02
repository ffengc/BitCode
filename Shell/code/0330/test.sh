# !/bin/bash

if 0;then
# 变量的赋值和使用，转义字符
var=10
echo "The number is $var"
echo -e "Username: $USER\tHOME directory: $HOME\n"

# ${}
LOGDIR="/usr/bin/"
echo "The Log file is ${LOGDIR}/message"
fi

LIST="one two three"
for var in $LIST
do
    echo "$var"     # 将变量LIST的值分成了3个参数传递给了for循环
done
echo -e ""
for var in "$LIST"
do 
    echo "$var"     # 将变量LIST的值作为一个整体传入for循环
done
