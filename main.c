/*���ݽṹ��һ����ҵ��ʵ��˳���Ķ��Ԫ�ز����ɾ��
	18184204-������*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define LIST_INT_SIZE 100 //���Ա���ռ�ĳ�ʼ������
#define LIST_INCREMENT 10//���Ա���ռ�ķ�������

typedef struct
{
	int* elem; //����ռ��ַ
	int length; //��ǰ����
	int listsize; //��ǰ����Ĵ�������
}SqList;

int InitList_Sq(SqList *L) //��ʼ�����Ա�L
{
	L->elem = (int*)malloc(LIST_INT_SIZE * sizeof(int));
	if (!L->elem)
	{
		return 0; //�������ʧ��
	}
	L->length = 0; //�ձ���Ϊ0
	L->listsize = LIST_INCREMENT; //��ʼ��������
	return 1; //��ʼ���ɹ�
}

int ListInsert_Sq(SqList *L, int e)
{
	if (L->length >= L->listsize) //��ǰ����ռ����������ӷ���
	{
		int *newbase = (int*)realloc(L->elem, (L->listsize + LIST_INCREMENT) * sizeof(int));
		if(!newbase) //�������ʧ��
		{
			return 0;
		}
		L->elem = newbase; //�»�ַ
		L->listsize += LIST_INCREMENT; //���Ӵ�������
	}
	L->elem[L->length] = e; //����e
	++L->length; //����1
	return 1; //����ɹ�
}

void Listprintf_Sq(SqList* L) //������Ա��ֵ
{
	for (int p = 0; p < L->length; p++)
	{
		printf("%d ",L->elem[p]);
	}
	printf("\n");
}

int ListDelete_Sq(SqList* L, int e) //ɾ�����Ա��е�ָ��Ԫ��
{
	int flag =  0; //��ʾ����ɾ��Ԫ��
	for (int p = 0; p < L->length; p++)
	{
		if (L->elem[p] == e)
		{
			for (int i = p + 1; i < L->length; i++)
			{
				L->elem[i - 1] = L->elem[i];
			}
			--L->length;
			p--; //�±�������һλ
			flag = 1;
		}
	}
	return flag;
}

void DestroyList(SqList* L) //�ݻ�˳���L
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
	SqList L; //�����µ����Ա�L
	int len; //Ҫ��ӵ����ֵ�����
	int e;
	if (! InitList_Sq(&L))//��ʼ���±�L
	{
		printf("����ʧ��");
		return 0;
	}
	printf("������Ҫ��ӵ����ֵ�������");
	scanf("%d",&len);
	printf("������Ҫ�������Ա�Ҫ���ӵ����֣�");
	for (int i = 0; i < len; i++)
	{	
		scanf("%d", & e);
		if (! ListInsert_Sq(&L,e)) //�������е������뵽���Ա���
		{
			printf("����ʧ��");
			DestroyList(&L);
			return 0;
		}
	}
	printf("���Ա�����ݣ�");
	Listprintf_Sq(&L);
	printf("������Ҫɾ����ֵ��");
	scanf("%d", & e);
	if (! ListDelete_Sq(&L, e))
	{
		printf("���Ա����޴���");
	}
	else
	{
		Listprintf_Sq(&L);
	}
	DestroyList(&L);
	return 0;
}
