#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
using namespace std;

class Widget {
public:
	Widget() {}
	Widget(const Widget& x) {
		cout << "hello world" << endl;
	}
};
Widget f(Widget u)
{
	Widget v(u);
	Widget w = v;
	return w;
}
int main() {
	Widget x;
	Widget y = f(f(x));
	return 0;
}