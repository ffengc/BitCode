#pragma once
#include<stdio.h>
#include<memory.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#define NAME_MAX 20 //一个联系人名字的最大空间
#define SEX_MAX 5   //性别
#define TELE_MAX 12  //电话
#define ADDR_MAX 30  //地址  
#define DEFAULT_SZ 3 //默认初始容量大小-后面有需要会接着增容
//一个人的信息
typedef struct PeoInfo {
	char name[NAME_MAX];
	char sex[SEX_MAX];
	int age;
	char tele[TELE_MAX];
	char addr[ADDR_MAX];
}PeoInfo;

//静态版本
#if 0
typedef struct Contact {
	PeoInfo data[MAX];//可以存放1000个人的信息
	int sz;//记录通讯录种已经保存的信息个数
}Contact;
#endif

typedef struct Contact {
	PeoInfo* data;//可以存放
	int sz;
	int capacity;//记录最大容量
}Contact;



//实现的结构名称
//让代码的可读性提升了
enum Option {
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SORT,
	PRINT
};


void _initContact(Contact* pc);
void _addContact(Contact* pc);
void _printContact(const Contact* pc);
void _delContact(Contact* pc);
void _searchContact(const Contact* pc);
void _modifyContact(Contact* pc);
void _sortByAge(Contact* pc);
void _destroyContact(Contact* pc);
void _saveContact(const Contact* pc);