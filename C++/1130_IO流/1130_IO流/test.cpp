
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif


#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<fstream>
using namespace std;


//explicit禁止的是隐式类型转换，强转不禁



//文本读写和二进制读写
//二进制读写：内存中如何存储，就如何输出出去
// 优点：快 缺点：写出去内容看不见
// 
//文本读写：序列化成字符串输出，读的也是字符串，反序列化成对象数据
// 优点：可以看见写出去是什么 缺点：存在一个转换过程，要慢一些


struct Date
{
	friend ostream& operator<<(ostream& out, const Date& d)
	{
		out << d._year << " " << d._month << " " << d._day;
		return out;
	}
	friend istream& operator>>(istream& in, Date& d)
	{
		in >> d._year >> d._month >> d._day;
		return in;
	}
public:
	Date(int year = 1, int month = 1, int day = 1)
		:_year(year), _month(month), _day(day) {}
	operator bool()
	{
		//这个是随机写的，假设输入_year为0，则结束
		if (_year == 0)return false;
		else return true;
	}
protected:
	int _year; int _month; int _day;
};

//例子
struct ServerInfo
{
	//char _address[32];
	//注意，如果把char[]改成string，就会出问题
	//改成string之后，写出去的结构会发生一些改变，然后读进来的时候，出现了内存问题（如果程序分两次运行）
	//因为重新启动程序，指针的地址就对不上了
	string _address;
	int _port;
	Date _date;
	friend ostream& operator<<(ostream& out, const ServerInfo& si)
	{
		cout << "address: " << si._address << endl;
		cout << "port: " << si._port << endl;
		cout << "Date: " << si._date << endl;
		return out;
	}
	ServerInfo(const string& s = " ", const int& port = 0, const Date& d = { 0,0,0 })
		:_address(s), _port(port), _date(d) {}
};
struct ConfigManager
{
public:
	ConfigManager(const char* filename = "server.txt")
		:_filename(filename) {}

	void WriteBin(const ServerInfo& info)
	{
		ofstream ofs(_filename, ios_base::out | ios_base::binary);//第二个参数是打开方式，可以不写
		//如果要用多个状态，就 | 在一起
		//默认的写操作是覆盖写 ，当然也有一个追加写，要用可以查文档
		ofs.write((char*)&info, sizeof(info));
	}
	void ReadBin(ServerInfo& info)
	{
		ifstream ifs(_filename, ios_base::in | ios_base::binary);
		ifs.read((char*)&info, sizeof(info));
	}
#if 0
	void WriteText1(const ServerInfo& info)
	{
		ofstream ofs(_filename, ios_base::out);
		ofs.write(info._address.c_str(), info._address.size());
		ofs.put('\n');//中间换一下行
		const string str = to_string(info._port);
		ofs.write(str.c_str(), str.size());
	}
	void ReadText1(ServerInfo& info)
	{
		ifstream ifs(_filename, ios_base::in);
		char buff[128];
		ifs.getline(buff, 128);
		info._address = buff;
		ifs.getline(buff, 128);
		info._port = stoi(buff);
	}
#endif
	//用流插入和流提取，更方便
	void WriteText2(const ServerInfo& info)
	{
		ofstream ofs(_filename, ios_base::out);
		ofs << info._address << endl;
		ofs << info._port << endl;
		ofs << info._date << endl;
	}
	void ReadText2(ServerInfo& info)
	{
		ifstream ifs(_filename, ios_base::in);
		ifs >> info._address >> info._port >> info._date;
	}
	//但是这种方法很麻烦，如果结构体里面数据复杂，就很难搞了，比如，ServerInfo里面有个日期类
protected:
	string _filename;
};

#if 0
int main()
{
	//Date d1(2022, 11, 28);
	//ServerInfo winfo = { "127.0.0.1",888, {2022,11,28} };
	ConfigManager cm;
	////////cm.WriteBin(winfo);//写出去
	//////cm.WriteText1(winfo);
	//cm.WriteText2(winfo);

	//现在想要读进来
	ServerInfo rinfo;
	//cm.ReadBin(rinfo);
	//cm.ReadText1(rinfo);
	cm.ReadText2(rinfo);
	cout << rinfo << endl;
	return 0;
}
#endif

//因此我们认为，二进制读写，不要写有动态内存的对象
//这也是一个局限性
//所以我们用[]而不是用string




//字符串流
//stringstream
#include<sstream>
//C语言 sprintf sscanf

struct ChatInfo
{
	string _name;
	int _id;
	Date _date;
	string _msg;
	friend ostream& operator<<(ostream& out, const ChatInfo& cif)
	{
		out << "name: " << cif._name << endl;
		out << "id: " << cif._id << endl;
		out << "date: " << cif._date << endl;
		out << "msg: " << cif._msg << endl;
		return out;
	}
};
int main()
{
	ChatInfo winfo = { "张三",135246,{2022,4,10},"晚上一起看电影吧" };
	ostringstream oss;
	oss << winfo._name << endl;
	oss << winfo._id << endl;
	oss << winfo._date << endl;
	oss << winfo._msg << endl;
	string info_str = oss.str();
	cout << info_str << endl;

	ChatInfo rinfo;
	//现在要把info_str解析出来
	istringstream iss(info_str);
	iss >> rinfo._name >> rinfo._id >> rinfo._date >> rinfo._msg;
	cout << rinfo << endl;
	return 0;
	//当然istringstream/ostringstream直接用一个stringstream就行
}