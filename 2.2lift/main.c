/***************数据结构第二次上机作业-lift-plussone***************/
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<malloc.h>
#define MaxSize 5   //电梯所能承载的最大人数
#define N 5

typedef struct        //************************** 乘客结构体
{
	int FloorofPerson;    //乘客所在楼层
	int GoFloor;         //乘客要去楼层
	int WaitingTime;      //乘客的最大容忍等待时间
	/*int Direction;        //方向
	int InorOut;          //乘客是否已出电梯
	int Leave;            //乘客是否离去*/
	int WaitedTime;       //乘客已经等待的时间
}Person;

typedef struct      //******************************电梯结构体
{
	int Floor;                //所在楼层
	int State;    //运行方向状态,-1向下，0停留，1向下
	int NumberofPerson;       //装载乘客人数
}Elevator;

Person Passenger[10][10];  //全局结构体二维数组保存整栋楼的乘客的相关信息

Person PassengerInElevator[15];   //在电梯中的乘客的相关信息存储在结构体一维数组中

Person PassengerOutElevator[MaxSize]; //下电梯的乘客

Elevator left; //定义电梯

int map[18][35] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
				   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
				   1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
				   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
				   1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
				   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
			       1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
				   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
			       1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
				   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
			       1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 
				   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //电梯情况数组
int b[10];            //每层楼的人数
/*int InCount[9];      //每层楼进入电梯的实际人数
int OutCount[9];     //每层楼走出电梯的实际人数*/
int tclock = 0;        //电梯运行时的全局软时钟
int add_t = 0;		   //电梯每层运行的时钟
/*int InTime[9];    //每层楼乘客进入电梯的时间
int OutTime[9];      //每层楼乘客出电梯的时间*/

void view(int chat,int d) //输出当前情况
{
	system("cls");
	for (int i = 0; i < 17; i++)
	{
		for (int j = 1; j <= 33; j++)
		{
			if (map[i][j])
			{
				printf("■");
			}
			else
			{
				if (1 <= j && j <= 12)
				{
					if ((i-1+d)/3 ==5-left.Floor&&(i-1+d)>=0)
					{
						if ((i+d) % 3 == 0)
						{
							printf("==");
						}
						else if (PassengerInElevator[j-1].WaitingTime != 0)
						{
							if((i+d) % 3 == 1)
							{
								printf("F%d", PassengerInElevator[j-1].GoFloor);
							}
							else if ((i+d) % 3 == 2)
							{
								printf(" #");
							}
							else
							{
								printf("12");
							}
						}
						else
						{
							printf("  ");
						}
					}
					else
					{
						printf("  ");
					}
				}
				else if (j == 13)
				{
					int bs = 0;
					for (int i = 0; i < left.NumberofPerson; i++)
						if (PassengerInElevator[i].GoFloor != left.Floor)
							bs++;
					if (5-left.Floor == (i-1)/3&&!d&&(b[left.Floor]|| bs != left.NumberofPerson))
					{
						printf("  ");
					}
					else
					{
						printf(" |");
					}
				}
				else if(14<=j&&j<=18)
				{
					if (Passenger[5 - (i-1)/3][j-14].WaitingTime != 0)
					{
						if (i % 3 == 1)
						{
							printf("F%d", Passenger[5 - (i - 1) / 3][j-14].GoFloor);
						}
						else if (i % 3 == 2)
						{
							printf(" #");
						}
					}
					else
					{
						printf("  ");
					}
				}
				else if(28<=j&&j<=32)
				{
					if (chat)
					{
						if ((i - 1) / 3 == 5 - chat && PassengerOutElevator[32 - j].WaitingTime != 0)
						{
							if (i % 3 == 1)
							{
								printf("F%d", PassengerOutElevator[32 - j].GoFloor);
							}
							else if (i % 3 == 2)
							{
								printf(" #");
							}
						}
						else
						{
							printf("  ");
						}
					}
					else
					{
						if ((i - 1) / 3 == 5 - left.Floor && PassengerOutElevator[32 - j].WaitingTime != 0)
						{
							if (i % 3 == 1)
							{
								printf("F%d", PassengerOutElevator[32 - j].GoFloor);
							}
							else if (i % 3 == 2)
							{
								printf(" #");
							}
						}
						else
						{
							printf("  ");
						}
					}

				}
				else
				{
					printf("  ");
				}
			}	
		}
		printf("\n");
	}
	//system("pause");
	Sleep(700);
}

void reset(int a,int x,int p) //删除等待的人或者电梯中的人
{
	if (a)
	{
		for (int i = p; i < 5; i++)
		{
			PassengerInElevator[i] = PassengerInElevator[i+1];
		}
	}
	else
	{
		for (int i = p; i < b[x]; i++)
		{
			Passenger[x][i] = Passenger[x][i + 1];	
		}
		b[x]--;
	}
}

int add_time(int time) //等待时间增加
{
	for (int i = 1; i <= 5; i++)
	{
		int k = 0;
		for (int j = 0; j < b[i]; j++)
		{
			Passenger[i][j].WaitedTime += time;
			if (Passenger[i][j].WaitingTime < Passenger[i][j].WaitedTime)
			{
				PassengerOutElevator[k] = Passenger[i][j];
				k++;
				reset(0, i, j);
				j--;
				view(i,0);
				printf("当前时间%d		在%d层超时离开一人\n", tclock, i);
				Sleep(700);
			}
		}
		memset(PassengerOutElevator, 0, sizeof(PassengerOutElevator));
	}
	return 0;
}

int In(int y, int x,int d)      //乘客进入电梯,每次乘客进入电梯后将该层的乘客重新排序( y表示电梯当前人数；x表示楼层)
{
	int m = y;           //保存电梯当前人数
	for (int p = 0; p < b[x]; p++)
	{
		if ((Passenger[x][p].GoFloor > x && d>=0) ||(Passenger[x][p].GoFloor < x && d <= 0))//该x层乘客p的方向与电梯方向一致且未离开，若电梯未满，则进电梯
		{
			if (m == MaxSize)
			{
				break;                 //该楼层的其他乘客等待一段时间
			}
			PassengerInElevator[m] = Passenger[x][p];
			m++;                        //电梯内人数增加
			reset(0,x,p); //删除电梯外的人
			p--;
			tclock += 2;
			add_t += 2;
			view(0,0);
			printf("当前时间%d		电梯在%d层进入一人\n",tclock,x);
			Sleep(700);
		}
	}
	return m;
}

int Out(int floor, int number)    //乘客出电梯，每次乘客出电梯将全局数组中的乘客信息重新修改，floor表示楼层，number表示电梯内人数
{
	int k = number;//电梯内剩余的人 
	for (int i = 0; i < MaxSize; i++)
	{
		if (PassengerInElevator[i].GoFloor == floor)
		{
			PassengerOutElevator[number - k]= PassengerInElevator[i];
			k--;
			reset(1, 0, i); //删除电梯中下来的人
			tclock += 2;
			add_t += 2;
			i--;
			view(0,0);
			printf("当前时间%d		电梯在%d层出去一人\n", tclock,floor);
			Sleep(700);
		}
	}
	memset(PassengerOutElevator, 0, sizeof(PassengerOutElevator));
	return k;
}

void Open()            //电梯开门
{
	tclock += 2;
	add_t += 2;
	view(0,0);
	printf("当前时间%d		电梯在%d层开门\n", tclock, left.Floor);
	Sleep(700);
}

void Close()           //电梯关门
{
	tclock += 2;
	add_t += 2;
	view(0,0);
	printf("当前时间%d		电梯在%d层关门\n", tclock, left.Floor);
	Sleep(700);
}

int Go(Elevator* ele)           //电梯正在运行
{
	Elevator* e = ele;	
	if (e->State == 1)
	{
		e->Floor++;
	}
	else if (e->State == -1)
	{
		e->Floor--;
	}
	for (int i = 2; i >= 0; i--)
	{	
		if (e->State == 1)
		{
			view(0, -1*i * e->State);			
			printf("电梯正在向上运行!!!!!!!\n");
			Sleep(700);
		}
		else if (e->State == -1)
		{
			view(0, -1*i * e->State);
			printf("电梯正在向下运行!!!!!!!\n");
			Sleep(700);
		}
		tclock += 1;
		add_t += 1;
	}
	return (e->Floor);
}

void Initialize()            //系统最开始的初始化
{
	srand(time(0));          //获取时间种子
	for (int i = 1; i <= 5; i++)//每层楼的人数随机初始化
	{
		b[i] = rand() % N;
		for (int k = 0; k < b[i]; k++)
		{
			Passenger[i][k].FloorofPerson = i;
			Passenger[i][k].WaitingTime = rand() % 100;
			Passenger[i][k].WaitedTime = 0;
		A:
			Passenger[i][k].GoFloor = rand() % 5 + 1;
			if (Passenger[i][k].GoFloor > 5 || Passenger[i][k].GoFloor == i)
			{
				goto A;
			}
		}
	}
}

int Test()             // 考查整栋楼有无请求  ，无返回0，有返回1；
{
	for (int cs = 1; cs < 5; cs++)
		if (b[cs] != 0)
			return cs;
	return 0;
}

void innew() //生成新乘客
{
	int i;
	B:
		i = rand() % 5+1;
		if (b[i] == 5)
		{
			goto B;
		}
		Passenger[i][b[i]].FloorofPerson = i;
		Passenger[i][b[i]].WaitingTime = rand() % 100;
		Passenger[i][b[i]].WaitedTime = 0;
	C:
		Passenger[i][b[i]].GoFloor = rand() % 5 + 1;
		if (Passenger[i][b[i]].GoFloor > 5 || Passenger[i][b[i]].GoFloor == i)
		{
			goto C;
		}
		b[i]++;
		view(i,0);
		printf("当前时间%d		有一名乘客来到%d层\n", tclock, i);
		Sleep(700);
}

void Run(Elevator* left) //电梯运行判断
{
	Elevator* ts = left;
	int floor = ts->Floor;    //保存电梯当前的所在楼层数
	int number = ts->NumberofPerson;   //保存电梯当前的人数
	int flag = 0;
	//循环次数

	while (flag != 15)
	{
		if (0 <= tclock % 40 && tclock % 40 <= 5)
		{
			innew();
		}
		if (!Test()&&!number)    //考查整栋楼有无请求  ，无返回0，有返回1;
		{
			flag++;
			tclock += 2;
			add_t = add_time(2);
			ts->State = 0;
			view(0,0);
			printf("当前时间:%d		电梯在%d层空闲等待\n", tclock, floor);
			Sleep(700);
		}
		else
		{
			if (ts->Floor == 5)
			{
				ts->State = -1;
			}
			else if (ts->Floor == 1)
			{
				ts->State = 1;
			}
			else if (ts->State == 0)
			{
				if (number)
				{
					ts->State = (PassengerInElevator[0].GoFloor >= ts->Floor) ? 1 : -1;
				}
				else
				{

					ts->State = (Test() >= ts->Floor) ? 1 : -1;
				}
			}
			flag = 0;
			int bs = 0;
			//printf("在%ld时刻电梯正在第%d层!\n", (double)(tclock*0.1), floor);
			for (int i = 0; i < number; i++)
				if (PassengerInElevator[i].GoFloor != floor)
					bs++;
			/*printf("%d,%d %d %d\n", floor, b[floor], bs, number);
			system("pause");*/
			if (b[floor] == 0 && bs == number)    //电梯外没人，没人下
			{
				add_t=add_time(add_t);
				//电梯不开门，继续上升或下降
				int ofloor = floor;
				floor = Go(ts);      //电梯移动
				printf("当前时间%d		没人在%d层上下电梯，电梯继续运行\n",tclock,ofloor);
			}
			else //电梯要上下人
			{
				add_t=add_time(add_t);
				Open();
				number = Out(floor,number);
				number = In(number,floor,ts->State);
				Close();
			}
		}
		left->NumberofPerson = number;
		Sleep(700);
	}
}

int main()//主函数
{
	left.State = 0;                   //电梯初始化
	left.Floor = 1;
	left.NumberofPerson = 0;
	Initialize();
	view(0,0);
	Run(&left);
	return 0;
}
