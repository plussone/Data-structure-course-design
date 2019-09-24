/*数据结构第一次作业：实现顺序表的多个元素插入和删除
	plussone*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define LIST_INT_SIZE 100 //线性表储存空间的初始分配量
#define LIST_INCREMENT 10//线性表储存空间的分配增量

typedef struct
{
	int* elem; //储存空间基址
	int length; //当前长度
	int listsize; //当前分配的储存容量
}SqList;

int InitList_Sq(SqList *L) //初始化线性表L
{
	L->elem = (int*)malloc(LIST_INT_SIZE * sizeof(int));
	if (!L->elem)
	{
		return 0; //储存分配失败
	}
	L->length = 0; //空表长度为0
	L->listsize = LIST_INCREMENT; //初始储存容量
	return 1; //初始化成功
}

int ListInsert_Sq(SqList *L, int e)
{
	if (L->length >= L->listsize) //当前储存空间已满，增加分配
	{
		int *newbase = (int*)realloc(L->elem, (L->listsize + LIST_INCREMENT) * sizeof(int));
		if(!newbase) //储存分配失败
		{
			return 0;
		}
		L->elem = newbase; //新基址
		L->listsize += LIST_INCREMENT; //增加储存容量
	}
	L->elem[L->length] = e; //插入e
	++L->length; //表长增1
	return 1; //插入成功
}

void Listprintf_Sq(SqList* L) //输出线性表的值
{
	for (int p = 0; p < L->length; p++)
	{
		printf("%d ",L->elem[p]);
	}
	printf("\n");
}

int ListDelete_Sq(SqList* L, int e) //删除线性表中的指定元素
{
	int flag =  0; //表示有无删除元素
	for (int p = 0; p < L->length; p++)
	{
		if (L->elem[p] == e)
		{
			for (int i = p + 1; i < L->length; i++)
			{
				L->elem[i - 1] = L->elem[i];
			}
			--L->length;
			p--; //下标向左移一位
			flag = 1;
		}
	}
	return flag;
}

void DestroyList(SqList* L) //摧毁顺序表L
{
	if (L->elem == NULL || L->length == 0)
	{
		return;
	}
	else
	{
		free(L->elem);
		L->length = 0;
	}
}

int main()
{
	SqList L; //建立新的线性表L
	int len; //要添加的数字的数量
	int e;
	if (! InitList_Sq(&L))//初始化新表L
	{
		printf("创建失败");
		return 0;
	}
	printf("请输入要添加的数字的数量：");
	scanf("%d",&len);
	printf("请输入要插入线性表要增加的数字：");
	for (int i = 0; i < len; i++)
	{	
		scanf("%d", & e);
		if (! ListInsert_Sq(&L,e)) //将数组中的数插入到线性表中
		{
			printf("插入失败");
			DestroyList(&L);
			return 0;
		}
	}
	printf("线性表的数据：");
	Listprintf_Sq(&L);
	printf("请输入要删除的值：");
	scanf("%d", & e);
	if (! ListDelete_Sq(&L, e))
	{
		printf("线性表中无此数");
	}
	else
	{
		Listprintf_Sq(&L);
	}
	DestroyList(&L);
	return 0;
}
