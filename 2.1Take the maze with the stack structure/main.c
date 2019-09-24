/*���ݽṹ�ڶ�����ҵ��ʵ�̶ֹ���ͼѰ�ҳ���·��
	18184204-������  */
#define _CRT_SECURE_NO_WARNINGS

#define STACK_INIT_SIZE 100//ջ�������ռ���
#define STACKINCREMENT 10//����ռ������

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int map[10000][10000], vis[10000][10000], dir[5][2] = { {0,0},{0,-1},{0,1},{1,0},{-1,0} }; //��ͼ����ǡ���������
int a = 10, b = 10; //��ͼ�Ŀ�ͳ�
int x1 = 1, y1 = 0, x2 = 1, y2 = 9; //�����յ�λ��

struct Node //�Թ��ڵ�
{
	int x; //x����
	int y; //y����
	int dirn; //������
};

struct SqStack
{
	struct Node* base; //ջ��ָ��
	struct Node* top; //ջ��ָ��
	int stacksize; //��������
};

int InitStack(struct SqStack* S) //��ʼ����ջS
{
	S->base = (struct Node*)malloc(STACK_INIT_SIZE * sizeof(struct Node));
	if (!S->base)
	{
		return 0; //�ռ����ʧ��
	}
	S->stacksize = STACK_INIT_SIZE;
	S->top = S->base;
	return 1;
}

int Push(struct SqStack* S, int x, int y, int d) //��ջ��������Ԫ��
{
	if ((S->top) - (S->base) >= S->stacksize)
	{
		S->base = (struct Node*)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(struct Node)); //ջ����׷�Ӵ洢�ռ�
		if (!S->base)
		{
			return 0; //����ʧ��
		}
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	S->top->x = x;
	S->top->y = y;
	S->top->dirn = d;
	S->top++;
	return 1;
}

struct Node* Gettop(struct SqStack* S) //���ջ����ֵ
{
	if (S->top == S->base)
	{
		return NULL; //ջΪ��
	}
	else
	{
		return (S->top) - 1;
	}
}

struct Node* Pop(struct SqStack* S) //ɾ��ջ��Ԫ��,�������ֵ
{
	if (S->top == S->base)
	{
		return NULL; //ջΪ��
	}
	return --(S->top);
}

void SqStack_print(struct SqStack* S) //����Թ�·��
{
	struct SqStack* L = (struct SqStack*)malloc(sizeof(struct SqStack)); //����һ����
	if (!InitStack(L)) //��ʼ���±�L
	{
		printf("������ջʧ��\n");
		return;
	}
	struct Node* now1 = (struct Node*)malloc(sizeof(struct Node)); //����һ����ʱ����ṹ��
	while (Gettop(S))
	{
		//printf("100");
		now1 = Pop(S);
		if (!Push(L, now1->x, now1->y, 0))
		{
			printf("�����ջʧ��\n");
			return;
		}
	}
	printf("�Թ�·��Ϊ��");
	while (Gettop(L))
	{
		now1 = Pop(L);
		printf("(%d,%d) ", now1->x + 1, now1->y + 1);
	}
	free(now1);
}

void makemap()
{

}

void sacnfdata()
{
	printf("�������Թ��ĳ��Ϳ�");
	scanf("%d%d", &b, &a);
	printf("���������λ�ã�");
	scanf("%d%d", &x1, &y2);
	printf("�������յ�λ�ã�");
	scanf("%d%d", &x2, &y2);
	system("cls");
}

int main()
{
	sacnfdata();
	makemap();
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			if (map[i][j] == 0)
			{
				printf("  ");
			}
			else
			{
				printf("��");
			}
		}
		printf("\n");
	}
	struct SqStack* S = (struct SqStack*)malloc(sizeof(struct SqStack)); //����һ��ջ��
	memset(vis, 0, sizeof(vis)); //��ʼ���������
	if (!InitStack(S)) //��ʼ���±�L
	{
		printf("������ջʧ��\n");
		return 0;
	}
	struct Node* now = (struct Node*)malloc(sizeof(struct Node)); //������ʱ����ṹ��
	now->x = x1;
	now->y = y1;
	if (!Push(S, x1, y1, 1)) //��ڽ�ջ
	{
		printf("�����ջʧ��\n");
		return 0;
	}
	int flag = 0; //����·�߱�־
	while (Gettop(S))
	{
		now = Gettop(S);
		if (now->x == x2 && now->y == y2) //�ҵ����ڽ���
		{
			flag = 1;
			break;
		}
		else if (vis[now->x][now->y] == 5) //�Ҳ�����һ��Ԫ�ط���
		{
			Pop(S);
			continue;
		}
		else
		{
			int d = 0; //������
			if (vis[now->x][now->y] == 1)
			{
				d = 2;
			}
			else if (vis[now->x][now->y] == 2)
			{
				d = 1;
			}
			else if (vis[now->x][now->y] == 3)
			{
				d = 4;
			}
			else if (vis[now->x][now->y] == 4)
			{
				d = 3;
			}
			//printf("%d %d\n", now->x + dir[vis[now->x][now->y]][0], now->y + dir[vis[now->x][now->y]][1]);
			if (now->x + dir[vis[now->x][now->y]][0] < 0 || now->x + dir[vis[now->x][now->y]][0] >= a || now->y + dir[vis[now->x][now->y]][1] < 0 || now->y + dir[vis[now->x][now->y]][1] >= b) //�±�Խ��
			{
				vis[now->x][now->y]++;
				continue;
			}
			else if (map[now->x][now->y] == 1 || now->dirn == vis[now->x][now->y] || vis[now->x][now->y] == 0) //����ǽ���ػ����������򷵻ػ�ԭ�ز���
			{
				//printf("1000\n");
				vis[now->x][now->y]++;
				continue;
			}
			else if (!Push(S, now->x + dir[vis[now->x][now->y]][0], now->y + dir[vis[now->x][now->y]][1], d)) //������һ������
			{
				vis[now->x][now->y]++;
				printf("�����ջʧ��\n");
				return 0;
			}
			//printf("%d %d\n", now->x, now->y);
			vis[now->x][now->y]++;
		}
	}
	/*for(int i =0;i<10;i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printf("%d ", vis[i][j]);
		}
		printf("\n");
	}*/
	if (flag == 0)
	{
		printf("�Թ�û��ͨ·\n");
	}
	else
	{
		SqStack_print(S);
	}
	free(S->base); //�ͷ�ջ�ڴ�ռ�
	free(S);
	return 0;
}
