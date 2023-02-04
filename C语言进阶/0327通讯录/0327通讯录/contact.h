#pragma once
#include<stdio.h>
#include<memory.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#define MAX 1000
#define NAME_MAX 20
#define SEX_MAX 5
#define TELE_MAX 12
#define ADDR_MAX 30
//一个人的信息
typedef struct PeoInfo {
	char name[NAME_MAX];
	char sex[SEX_MAX];
	int age;
	char tele[TELE_MAX];
	char addr[ADDR_MAX];
}PeoInfo;
typedef struct Contact {
	PeoInfo data[MAX];//可以存放1000个人的信息
	int sz;//记录通讯录种已经保存的信息个数
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