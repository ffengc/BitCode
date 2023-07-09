#define _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<algorithm>
#include<stack>
#include<queue>
#include<vector>
#include<string>
using namespace std;


//stack_queue 简单简单简单！
//没有迭代器 -- 要保持stack_queue的特性

void test_stack() {
	stack<int>st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);

	while (!st.empty()) {
		cout << st.top() << endl;
		st.pop();
	}
}
void test_queue() {
	queue<int>q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);

	while (!q.empty()) {
		cout << q.front() << endl;
		q.pop();
	}
}

int main() {
	//test_stack();
	test_queue();
	return 0;
}



//155. 最小栈
//要求O(1)
class MinStack {
private:
    int _min;
    stack<int>st;//正常栈
    stack<int>minst;//记录最小数据的栈
    //如果有大量重复数据怎么办？
    //minst里面存大量相同的数据吗？ -- 我们加一个计数器就行了
    //minst里面不存数字，存一个结构体就行
public:
    void push(int val) {
        st.push(val);
        if (minst.empty() || val <= minst.top()) { //如果空或者小于等于，minst也插入
            minst.push(val);
        }
    }
    void pop() {
        if (minst.top() == st.top()) {
            minst.pop();
        }
        st.pop();
    }
    int top() {
        return st.top();
    }
    int getMin() {
        return minst.top();
    }
};


//JZ31 栈的压入、弹出序列
//判断栈序列
class Solution {
public:
    bool IsPopOrder(vector<int> pushV, vector<int> popV) {
        int i = 0;
        int j = 0;
        stack<int>st;
        while (j < popV.size()) {
            if (!st.empty() && st.top() == popV[j]) {
                st.pop();
                j++;
            }
            else {
                if (i < pushV.size()) {
                    st.push(pushV[i]);
                    i++;
                }
                else return false;
            }
        }
        return true;
    }
};


//150. 逆波兰表达式求值
//中缀表达式
//1+2*3  --  这样计算机是算不了的，因为不知道优先级
//后缀表达式
//1 2 3 * +  这样就可以算了

//后缀怎么算：（先解决后缀怎么算，然后再研究中缀怎么转后缀）
//操作数的顺序不变
//1.操作数入栈
//2.操作符就取栈顶的连续两个数据运算，运算结果入栈
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<long long>st;
        for (auto& str : tokens) {
            if (str == "+" || str == "-" || str == "*" || str == "/") {
                //直接用字符串operator==去判断，以免'-'和负数误判
                long long right = st.top();
                st.pop();
                long long left = st.top();
                st.pop();
                switch (str[0]) {
                case '+':
                    st.push(left + right);
                    break;
                case '-':
                    st.push(left - right);
                    break;
                case '*':
                    st.push(left * right);
                    break;
                case '/':
                    st.push(left / right);
                    break;
                }
            }
            else {
                st.push(stoi(str));
            }
        }
        return st.top();
    }
};
//中缀转后缀：
//1.遇到操作数：输出
//2.遇到操作符
// a.栈为空，或者比栈顶的操作符优先级高，入栈
// b.比栈顶的操作符优先级低或者相等，出栈顶的运算符