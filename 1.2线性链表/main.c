/*数据结构第一次作业：实现链表删除重复元素
	plussone  */
#define _CRT_SECURE_NO_WARNINGS

#define MAX_LENGTH 15//链表最大长度

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	struct Node* next; //储存空间基址
	int data; //储存数据
};

struct Node* head = NULL;

void InitList_Sq() //初始化链表L
{
	head = (struct Node*)malloc(sizeof(struct Node));
	head->data = 0;
	head->next = NULL;
}

void ListInsert_Sq(struct Node* L, int e) //增加节点
{
	struct Node* pnew = (struct Node*)malloc(sizeof(struct Node));
	L->next = pnew;
	pnew->data = e;
	pnew->next = NULL;
	head->data++;
}

void sjsc(struct Node* L) //给链表L随机生成值
{
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		ListInsert_Sq(L, rand() % 10); //随机添加0-9之间的数
		L = L->next;
	}
}

void Listprintf_Sq(struct Node* L) //输出链表的值
{
	while (L != NULL && L->next != NULL)
	{
		printf("%d ", (L->next)->data);
		L = L->next;
	}
}

void ListDelete_Sq(struct Node* L) //删除线性表中的指定元素
{
	struct Node* pnew = L->next;
	L->next = (pnew->next);
	free(pnew);
	head->data--;
	return ;
}

void sccfz(struct Node* L) //删除链表中的重复值
{
	struct Node* pnew = L;
	int vist[10]; //标记数组
	memset(vist, 0, sizeof(vist));
	while(L->next != NULL)
	{
		vist[(L->next)->data]++;
		L = L->next;
	}
	L = pnew;
	while (L->next != NULL)
	{
		if (vist[(L->next)->data] > 1)
		{
			ListDelete_Sq(L);
		}
		else
		{
			L = L->next;
		}
	}
}

void DestroyList() //摧毁链表
{
	if (head == NULL)
	{
		return ;
	}
	while(head->next != NULL)
	{
		ListDelete_Sq(head);
	}
	free(head);
	return ;
}

int main()
{
	InitList_Sq(); //初始化新表L
	sjsc(head); //随机生成数据
	printf("链表的初始数据：");
	Listprintf_Sq(head); //输出链表的值
	printf("删除重复后的值：");
	sccfz(head);
	Listprintf_Sq(head); //输出链表的值
	DestroyList(head);
	return 0;
}


