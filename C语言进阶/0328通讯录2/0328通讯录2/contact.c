#define _CRT_SECURE_NO_WARNINGS 1

#include"contact.h"

//初始化通讯录(静态)
#if 0
void _initContact(Contact* pc) {
	assert(pc);
	pc->sz = 0;
	memset(pc->data, 0, sizeof(pc->data));
}
#endif

//动态版本初始化
void _initContact(Contact* pc) {
	assert(pc);
	pc->sz = 0;
	pc->capacity = DEFAULT_SZ;
	pc->data =(PeoInfo*)malloc(pc->capacity * sizeof(PeoInfo));
	if (pc->data == NULL) {
		perror("init::malloc");
		exit(-1);
	}
	memset(pc->data, 0, pc->capacity * sizeof(PeoInfo));
}

//销毁通讯录
void _destroyContact(Contact* pc) {
	free(pc->data);
	pc->data = NULL;
	pc->capacity = 0;
	pc->sz = 0;
}

//增容
void _checkCapacity(Contact* pc) {
	if (pc->sz == pc->capacity) {
		PeoInfo* tmp = (PeoInfo*)realloc(pc->data, (pc->capacity + 2) * sizeof(PeoInfo));
		if (tmp != NULL) {
			pc->data = tmp;
		}
		pc->capacity += 2;
		printf("contact is successfully enlarged!\n");
		printf("---------------------------------\n");
	}
}
//增加联系人
void _addContact(Contact* pc) {
	assert(pc);
	//if (pc->sz == MAX) {
	//	printf("Contact is already full,err\n");
	//	exit(-1);
	//}
	
	//满了要增容
	_checkCapacity(pc);
	//录入信息
	printf("please input the name:");
	scanf("%s", pc->data[pc->sz].name);
	printf("please input the age:");
	scanf("%d", &(pc->data[pc->sz].age));
	printf("please input the sex:");
	scanf("%s", pc->data[pc->sz].sex);
	printf("please input the tele_num:");
	scanf("%s", pc->data[pc->sz].tele);
	printf("pleae input the address:");
	scanf("%s", pc->data[pc->sz].addr);

	pc->sz++;
	printf("----------------------------\n");
	printf("successfully added!\n");
	printf("----------------------------\n");
	printf("\n");
	system("pause");
}

//打印通讯录
void _printContact(const Contact* pc) {
	assert(pc);
	//打印
	int i = 0;
	printf("\n");
	printf("%-20s %-5s %-5s %-12s %-30s\n", "姓名", "年龄", "性别", "电话", "地址");
	for (i = 0; i < pc->sz; i++) {
		printf("%-20s %-5d %-5s %-12s %-30s\n", pc->data[i].name, pc->data[i].age,
			pc->data[i].sex, pc->data[i].tele, pc->data[i].addr);
	}
	printf("\n");
	system("pause");
}

//通过名字查找人的信息
int _findByName(const Contact* pc, char* name) {
	assert(pc);
	int i = 0;
	for (i = 0; i < pc->sz; i++) {
		if (strcmp(pc->data[i].name, name) == 0) {
			return i;
		}
	}
	return -1;
}

//删除指定联系人信息
void _delContact(Contact* pc) {
	assert(pc);
	if (pc->sz == 0) {
		printf("null Contact! err!\n");
		system("pause");
		return;
	}
	//删除
	//1.找到
	char name[NAME_MAX] = { 0 };
	printf("please input the name：");
	scanf("%s", name);
	int pos = _findByName(pc, name);//找到了，返回下标；找不到，返回负一
	if (pos == -1) {
		printf("cannot find the PeoInfo,err!");
		system("pause");
		return;
	}
	//2.删除
	//这里要稍微分析清楚，是sz-1，不要越界了
	for (int j = pos; j < pc->sz - 1; j++) {
		pc->data[j] = pc->data[j + 1];
	}
	pc->sz--;//这个不要忘记了
	printf("successfully deleted\n");
	system("pause");
}



//查找一个人的信息
void _searchContact(const Contact* pc) {
	char name[NAME_MAX] = { 0 };
	printf("please input the name:>");
	scanf("%s", name);
	int pos = _findByName(pc, name);
	if (pos == -1) {
		printf("cannot find the PeoInfo,err!");
		return;
	}
	printf("--------------------------------------------------\n");
	printf("the info is:\n");
	printf("%-20s %-5s %-5s %-12s %-30s\n", "姓名", "年龄", "性别", "电话", "地址");
	printf("%-20s %-5d %-5s %-12s %-30s\n", pc->data[pos].name, pc->data[pos].age,
		pc->data[pos].sex, pc->data[pos].tele, pc->data[pos].addr);
	printf("--------------------------------------------------\n");
	system("pause");
}


void _modifyContact(Contact* pc) {
	printf("whose Info do you want to modify:\n");
	char name[NAME_MAX] = { 0 };
	scanf("%s", name);
	int pos = _findByName(pc, name);
	if (pos == -1) {
		printf("cannot find the PeoInfo,err!\n");
		printf("--------------------------------------------------\n");
		system("pause");
		return;
	}
	//修改
	printf("--------------------------------------------------\n");
	printf("you are modifing %s's info\n", pc->data[pos].name);
	printf("please input the name:");
	scanf("%s", pc->data[pos].name);
	printf("please input the age:");
	scanf("%d", &(pc->data[pos].age));
	printf("please input the sex:");
	scanf("%s", pc->data[pos].sex);
	printf("please input the tele_num:");
	scanf("%s", pc->data[pos].tele);
	printf("pleae input the address:");
	scanf("%s", pc->data[pos].addr);
	printf("\n");
	printf("successfully modified!\n");
	printf("--------------------------------------------------\n");
	printf("\n");
	system("pause");
}


int cmp(const void* e1, const void* e2) {
	//括号不要忘记了
	return (((PeoInfo*)e1)->age - ((PeoInfo*)e1)->age);
}
void _sortByAge(Contact* pc) {
	printf("sort by Age!\n");
	printf("--------------------------------------------------\n");
	qsort(pc->data, pc->sz, sizeof(PeoInfo), cmp);
	_printContact(pc);
}
//排序出了问题