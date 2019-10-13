/*数据结构第三次作业：实现固定地图寻找出口路线
	 plussone */
#define _CRT_SECURE_NO_WARNINGS

#define STACK_INIT_SIZE 100//栈最初分配空间量
#define STACKINCREMENT 10//储存空间分配量

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int map[10][10] = { 1,1,1,1,1,1,1,1,1,1,100000,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,100001,1,1};
int vis[100][100], dir[4][2] = {{0,-1},{0,1},{1,0},{-1,0}}; //地图、标记、方向数组
int a = 10, b = 10; //地图的宽和长
int x1 = 1, y1 = 0, x2 = 1, y2 = 9; //起点和终点位置
int flag = 0; //标记有无找到出口

struct Node //迷宫节点
{
	int x; //x坐标
	int y; //y坐标
};

struct SqStack
{
	struct Node* base; //栈顶指针
	struct Node* top; //栈顶指针
	int stacksize; //储存数据
};

int InitStack(struct SqStack** S) //初始化空栈S
{
	(*S)->base = (struct Node*)malloc(STACK_INIT_SIZE * sizeof(struct Node));
	if (!(*S)->base)
	{
		return 0; //空间分配失败
	}
	(*S)->stacksize = STACK_INIT_SIZE;
	(*S)->top = (*S)->base;
	return 1;
}

int Push(struct SqStack** S, int x, int y) //向栈顶插入新元素
{
	if (((*S)->top) - ((*S)->base) >= (*S)->stacksize)
	{
		(*S)->base = (struct Node*)realloc((*S)->base, ((*S)->stacksize + STACKINCREMENT) * sizeof(struct Node)); //栈满，追加存储空间
		if (!(*S)->base)
		{
			return 0; //分配失败
		}
		(*S)->top = (*S)->base + (*S)->stacksize;
		(*S)->stacksize += STACKINCREMENT;
	}
	(*S)->top->x = x;
	(*S)->top->y = y;
	(*S)->top++;
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
	if (!InitStack(&L)) //初始化新表L
	{
		printf("建立空栈失败\n");
		return;
	}
	struct Node* now1 = (struct Node*)malloc(sizeof(struct Node)); //建立一个临时坐标结构体
	while (Gettop(S))
	{
		//printf("100");
		now1 = Pop(S);
		if (!Push(&L, now1->x, now1->y))
		{
			printf("添加新栈失败\n");
			return;
		}
	}
	printf("迷宫路线为：");
	while (Gettop(L))
	{
		now1 = Pop(L);
		printf("(%d,%d) ", now1->y + 1, now1->x + 1);
	}
	free(now1);
}

void map_find(struct Sqstack*S)
{
	
	struct Node* now = (struct Node*)malloc(sizeof(struct Node)); //建立临时坐标结构体
	if (Gettop(S) == NULL)
	{
		return;
	}
	now = Gettop(S);
	if ((now->x == x2 && now->y == y2)||flag ==1)
	{
		flag = 1;
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		if (now->x + dir[i][0] < 0 || now->x + dir[i][0] >= a || now->y + dir[i][1] < 0 || now->y + dir[i][1] >= b) //下标越界
		{
			continue;
		}
		else if (map[now->x+dir[i][0]][now->y+dir[i][1]] == 1) //遇到墙返回
		{
			
			continue;
		}
		else if ((vis[now->x + dir[i][0]][now->y + dir[i][1]] > vis[now->x][now->y]+1)|| vis[now->x + dir[i][0]][now->y + dir[i][1]]==0) //访问路径较短
		{
			vis[now->x + dir[i][0]][now->y + dir[i][1]] = vis[now->x][now->y] + 1;
			if (!Push(&S, now->x + dir[i][0], now->y+dir[i][1])) //插入下一个方向
			{
				printf("添加新栈失败\n");
				continue;
			}
			map_find(S);
		}
	}
	if (flag == 0)
	{
		Pop(S);
	}
}

int main()
{
	printf("迷宫地图为：\n");
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			if (map[i][j] == 0)
			{
				printf("  ");
			}
			else if(map[i][j]==1)
			{
				printf("█");
			}
			else if (map[i][j] == 100000)
			{
				printf("入");
				x1 = i;
				y1 = j;
			}
			else if (map[i][j] == 100001)
			{
				printf("出");
				x2 = i;
				y2 = j;
			}
		}
		printf("\n");
	}
	struct SqStack* S = (struct SqStack*)malloc(sizeof(struct SqStack)); //建立一个栈堆
	memset(vis, 0, sizeof(vis)); //初始化标记数组
	if (!InitStack(&S)) //初始化新表L
	{
		printf("建立空栈失败\n");
		return 0;
	}
	if (!Push(&S, x1, y1)) //入口进栈
	{
		printf("添加新栈失败\n");
		return 0;
	}
	vis[x1][y1] = 1;
	map_find(S);
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
