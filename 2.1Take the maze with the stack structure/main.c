/*数据结构第二次作业：实现固定地图寻找出口路线
	plussone  */
#define _CRT_SECURE_NO_WARNINGS

#define STACK_INIT_SIZE 100//栈最初分配空间量
#define STACKINCREMENT 10//储存空间分配量

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int map[10000][10000], vis[10000][10000], dir[5][2] = { {0,0},{0,-1},{0,1},{1,0},{-1,0} }; //地图、标记、方向数组
int a = 10, b = 10; //地图的宽和长
int x1 = 1, y1 = 0, x2 = 1, y2 = 9; //起点和终点位置

struct Node //迷宫节点
{
	int x; //x坐标
	int y; //y坐标
	int dirn; //来方向
};

struct SqStack
{
	struct Node* base; //栈顶指针
	struct Node* top; //栈顶指针
	int stacksize; //储存数据
};

int InitStack(struct SqStack* S) //初始化空栈S
{
	S->base = (struct Node*)malloc(STACK_INIT_SIZE * sizeof(struct Node));
	if (!S->base)
	{
		return 0; //空间分配失败
	}
	S->stacksize = STACK_INIT_SIZE;
	S->top = S->base;
	return 1;
}

int Push(struct SqStack* S, int x, int y, int d) //向栈顶插入新元素
{
	if ((S->top) - (S->base) >= S->stacksize)
	{
		S->base = (struct Node*)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(struct Node)); //栈满，追加存储空间
		if (!S->base)
		{
			return 0; //分配失败
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

struct Node* Gettop(struct SqStack* S) //输出栈顶的值
{
	if (S->top == S->base)
	{
		return NULL; //栈为空
	}
	else
	{
		return (S->top) - 1;
	}
}

struct Node* Pop(struct SqStack* S) //删除栈顶元素,并输出其值
{
	if (S->top == S->base)
	{
		return NULL; //栈为空
	}
	return --(S->top);
}

void SqStack_print(struct SqStack* S) //输出迷宫路线
{
	struct SqStack* L = (struct SqStack*)malloc(sizeof(struct SqStack)); //建立一个堆
	if (!InitStack(L)) //初始化新表L
	{
		printf("建立空栈失败\n");
		return;
	}
	struct Node* now1 = (struct Node*)malloc(sizeof(struct Node)); //建立一个临时坐标结构体
	while (Gettop(S))
	{
		//printf("100");
		now1 = Pop(S);
		if (!Push(L, now1->x, now1->y, 0))
		{
			printf("添加新栈失败\n");
			return;
		}
	}
	printf("迷宫路线为：");
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
	printf("请输入迷宫的长和宽：");
	scanf("%d%d", &b, &a);
	printf("请输入起点位置：");
	scanf("%d%d", &x1, &y2);
	printf("请输入终点位置：");
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
				printf("█");
			}
		}
		printf("\n");
	}
	struct SqStack* S = (struct SqStack*)malloc(sizeof(struct SqStack)); //建立一个栈堆
	memset(vis, 0, sizeof(vis)); //初始化标记数组
	if (!InitStack(S)) //初始化新表L
	{
		printf("建立空栈失败\n");
		return 0;
	}
	struct Node* now = (struct Node*)malloc(sizeof(struct Node)); //建立临时坐标结构体
	now->x = x1;
	now->y = y1;
	if (!Push(S, x1, y1, 1)) //入口进栈
	{
		printf("添加新栈失败\n");
		return 0;
	}
	int flag = 0; //有无路线标志
	while (Gettop(S))
	{
		now = Gettop(S);
		if (now->x == x2 && now->y == y2) //找到出口结束
		{
			flag = 1;
			break;
		}
		else if (vis[now->x][now->y] == 5) //找不到下一个元素返回
		{
			Pop(S);
			continue;
		}
		else
		{
			int d = 0; //来方向
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
			if (now->x + dir[vis[now->x][now->y]][0] < 0 || now->x + dir[vis[now->x][now->y]][0] >= a || now->y + dir[vis[now->x][now->y]][1] < 0 || now->y + dir[vis[now->x][now->y]][1] >= b) //下标越界
			{
				vis[now->x][now->y]++;
				continue;
			}
			else if (map[now->x][now->y] == 1 || now->dirn == vis[now->x][now->y] || vis[now->x][now->y] == 0) //遇到墙返回或遇到来方向返回或原地不动
			{
				//printf("1000\n");
				vis[now->x][now->y]++;
				continue;
			}
			else if (!Push(S, now->x + dir[vis[now->x][now->y]][0], now->y + dir[vis[now->x][now->y]][1], d)) //插入下一个方向
			{
				vis[now->x][now->y]++;
				printf("添加新栈失败\n");
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
		printf("迷宫没有通路\n");
	}
	else
	{
		SqStack_print(S);
	}
	free(S->base); //释放栈内存空间
	free(S);
	return 0;
}
