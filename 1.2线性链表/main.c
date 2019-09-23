/*���ݽṹ��һ����ҵ��ʵ������ɾ���ظ�Ԫ��
	18184204-������  */
#define _CRT_SECURE_NO_WARNINGS

#define MAX_LENGTH 15//������󳤶�

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	struct Node* next; //����ռ��ַ
	int data; //��������
};

struct Node* head = NULL;

void InitList_Sq() //��ʼ������L
{
	head = (struct Node*)malloc(sizeof(struct Node));
	head->data = 0;
	head->next = NULL;
}

void ListInsert_Sq(struct Node* L, int e) //���ӽڵ�
{
	struct Node* pnew = (struct Node*)malloc(sizeof(struct Node));
	L->next = pnew;
	pnew->data = e;
	pnew->next = NULL;
	head->data++;
}

void sjsc(struct Node* L) //������L�������ֵ
{
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		ListInsert_Sq(L, rand() % 10); //������0-9֮�����
		L = L->next;
	}
}

void Listprintf_Sq(struct Node* L) //��������ֵ
{
	while (L != NULL && L->next != NULL)
	{
		printf("%d ", (L->next)->data);
		L = L->next;
	}
}

void ListDelete_Sq(struct Node* L) //ɾ�����Ա��е�ָ��Ԫ��
{
	struct Node* pnew = L->next;
	L->next = (pnew->next);
	free(pnew);
	head->data--;
	return ;
}

void sccfz(struct Node* L) //ɾ�������е��ظ�ֵ
{
	struct Node* pnew = L;
	int vist[10]; //�������
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

void DestroyList() //�ݻ�����
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
	InitList_Sq(); //��ʼ���±�L
	sjsc(head); //�����������
	printf("����ĳ�ʼ���ݣ�");
	Listprintf_Sq(head); //��������ֵ
	printf("ɾ���ظ����ֵ��");
	sccfz(head);
	Listprintf_Sq(head); //��������ֵ
	DestroyList(head);
	return 0;
}


