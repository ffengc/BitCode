#define _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

#if 0
int main(int argc, char* argv[])
{
	string a = "hello world";
	string b = a;
	if (a.c_str() == b.c_str())
	{
		cout << "true" << endl;       //两个字符串地址是不一样的 -- false
	}
	else cout << "false" << endl;

	string c = b;
	c = "";
	if (a.c_str() == b.c_str()) //false
	{
		cout << "true" << endl;
	}
	else cout << "false" << endl;

	a = "";
	if (a.c_str() == b.c_str())
	{
		cout << "true" << endl;
	}
	else cout << "false" << endl;
	return 0;
}
#endif

#if 0
int main()
{
	string str("Hello Bit.");
	str.reserve(111);
	str.resize(5);
	//Hello
	str.reserve(50);
	cout << str.size() << ":" << str.capacity() << endl;
	//
	return 0;
}
#endif

#if 0
int main(int argc, char* argv[])
{
	string strText = "How are you?";
	string strSeparator = " ";
	string strResult;
	int size_pos = 0;
	int size_prev_pos = 0;
	while ((size_pos = strText.find_first_of(strSeparator, size_pos)) != string::npos)
	{
		strResult = strText.substr(size_prev_pos, size_pos - size_prev_pos);
		cout << strResult << " ";
		size_prev_pos = ++size_pos;
	}
	if (size_prev_pos != strText.size())
	{
		strResult = strText.substr(size_prev_pos, size_pos - size_prev_pos);
		cout << strResult << " ";
	}
	cout << endl;
	return 0;
}
//How are you?
#endif


//字符转数字
class Solution {
private:
	bool is_Valid(string str) {
		//检查第一个字符
		if (!isdigit(str[0]) && str[0] != '+' && str[0] != '-') return false;
		//检查后面的字符
		for (int i = 1; i < str.size(); i++) {
			if (!isdigit(str[i]))return false;
		}
		return true;
	}
public:
	int StrToInt(string str) {
		int flag = 0;//表示正负
		if (!is_Valid(str))return 0;
		if (str[0] == '+')flag = 1;
		else if (str[0] == '-')flag = 0;
		else if (isdigit(str[0]))flag = 1;
		if (!isdigit(str[0])) {
			reverse(str.begin(), str.end());
			str.pop_back();//把正负号去掉
			reverse(str.begin(), str.end());
		}
		int sum = 0;
		for (int i = 0; i < str.size(); i++) {
			sum += pow(10, (str.size() - i - 1)) * (str[i] - '0');
		}
		if (flag == 0) {
			return -sum;
		}
		return sum;
	}
};
int main() {
	string s = "-123";
	cout << Solution().StrToInt(s) << endl;
	return 0;
}