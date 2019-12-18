
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<malloc.h>
#define MaxSize 5   //�������ܳ��ص��������
#define N 5

typedef struct        //************************** �˿ͽṹ��
{
	int FloorofPerson;    //�˿�����¥��
	int GoFloor;         //�˿�Ҫȥ¥��
	int WaitingTime;      //�˿͵�������̵ȴ�ʱ��
	/*int Direction;        //����
	int InorOut;          //�˿��Ƿ��ѳ�����
	int Leave;            //�˿��Ƿ���ȥ*/
	int WaitedTime;       //�˿��Ѿ��ȴ���ʱ��
}Person;

typedef struct      //******************************���ݽṹ��
{
	int Floor;                //����¥��
	int State;    //���з���״̬,-1���£�0ͣ����1����
	int NumberofPerson;       //װ�س˿�����
}Elevator;

Person Passenger[10][10];  //ȫ�ֽṹ���ά���鱣������¥�ĳ˿͵������Ϣ

Person PassengerInElevator[15];   //�ڵ����еĳ˿͵������Ϣ�洢�ڽṹ��һά������

Person PassengerOutElevator[MaxSize]; //�µ��ݵĳ˿�

Elevator left; //�������

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
				   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //�����������
int b[10];            //ÿ��¥������
/*int InCount[9];      //ÿ��¥������ݵ�ʵ������
int OutCount[9];     //ÿ��¥�߳����ݵ�ʵ������*/
int tclock = 0;        //��������ʱ��ȫ����ʱ��
int add_t = 0;		   //����ÿ�����е�ʱ��
/*int InTime[9];    //ÿ��¥�˿ͽ�����ݵ�ʱ��
int OutTime[9];      //ÿ��¥�˿ͳ����ݵ�ʱ��*/

void view(int chat,int d) //�����ǰ���
{
	system("cls");
	for (int i = 0; i < 17; i++)
	{
		for (int j = 1; j <= 33; j++)
		{
			if (map[i][j])
			{
				printf("��");
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

void reset(int a,int x,int p) //ɾ���ȴ����˻��ߵ����е���
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

int add_time(int time) //�ȴ�ʱ������
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
				printf("��ǰʱ��%d		��%d�㳬ʱ�뿪һ��\n", tclock, i);
				Sleep(700);
			}
		}
		memset(PassengerOutElevator, 0, sizeof(PassengerOutElevator));
	}
	return 0;
}

int In(int y, int x,int d)      //�˿ͽ������,ÿ�γ˿ͽ�����ݺ󽫸ò�ĳ˿���������( y��ʾ���ݵ�ǰ������x��ʾ¥��)
{
	int m = y;           //������ݵ�ǰ����
	for (int p = 0; p < b[x]; p++)
	{
		if ((Passenger[x][p].GoFloor > x && d>=0) ||(Passenger[x][p].GoFloor < x && d <= 0))//��x��˿�p�ķ�������ݷ���һ����δ�뿪��������δ�����������
		{
			if (m == MaxSize)
			{
				break;                 //��¥��������˿͵ȴ�һ��ʱ��
			}
			PassengerInElevator[m] = Passenger[x][p];
			m++;                        //��������������
			reset(0,x,p); //ɾ�����������
			p--;
			tclock += 2;
			add_t += 2;
			view(0,0);
			printf("��ǰʱ��%d		������%d�����һ��\n",tclock,x);
			Sleep(700);
		}
	}
	return m;
}

int Out(int floor, int number)    //�˿ͳ����ݣ�ÿ�γ˿ͳ����ݽ�ȫ�������еĳ˿���Ϣ�����޸ģ�floor��ʾ¥�㣬number��ʾ����������
{
	int k = number;//������ʣ����� 
	for (int i = 0; i < MaxSize; i++)
	{
		if (PassengerInElevator[i].GoFloor == floor)
		{
			PassengerOutElevator[number - k]= PassengerInElevator[i];
			k--;
			reset(1, 0, i); //ɾ����������������
			tclock += 2;
			add_t += 2;
			i--;
			view(0,0);
			printf("��ǰʱ��%d		������%d���ȥһ��\n", tclock,floor);
			Sleep(700);
		}
	}
	memset(PassengerOutElevator, 0, sizeof(PassengerOutElevator));
	return k;
}

void Open()            //���ݿ���
{
	tclock += 2;
	add_t += 2;
	view(0,0);
	printf("��ǰʱ��%d		������%d�㿪��\n", tclock, left.Floor);
	Sleep(700);
}

void Close()           //���ݹ���
{
	tclock += 2;
	add_t += 2;
	view(0,0);
	printf("��ǰʱ��%d		������%d�����\n", tclock, left.Floor);
	Sleep(700);
}

int Go(Elevator* ele)           //������������
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
			printf("����������������!!!!!!!\n");
			Sleep(700);
		}
		else if (e->State == -1)
		{
			view(0, -1*i * e->State);
			printf("����������������!!!!!!!\n");
			Sleep(700);
		}
		tclock += 1;
		add_t += 1;
	}
	return (e->Floor);
}

void Initialize()            //ϵͳ�ʼ�ĳ�ʼ��
{
	srand(time(0));          //��ȡʱ������
	for (int i = 1; i <= 5; i++)//ÿ��¥�����������ʼ��
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

int Test()             // ��������¥��������  ���޷���0���з���1��
{
	for (int cs = 1; cs < 5; cs++)
		if (b[cs] != 0)
			return cs;
	return 0;
}

void innew() //�����³˿�
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
		printf("��ǰʱ��%d		��һ���˿�����%d��\n", tclock, i);
		Sleep(700);
}

void Run(Elevator* left) //���������ж�
{
	Elevator* ts = left;
	int floor = ts->Floor;    //������ݵ�ǰ������¥����
	int number = ts->NumberofPerson;   //������ݵ�ǰ������
	int flag = 0;
	//ѭ������

	while (flag != 15)
	{
		if (0 <= tclock % 40 && tclock % 40 <= 5)
		{
			innew();
		}
		if (!Test()&&!number)    //��������¥��������  ���޷���0���з���1;
		{
			flag++;
			tclock += 2;
			add_t = add_time(2);
			ts->State = 0;
			view(0,0);
			printf("��ǰʱ��:%d		������%d����еȴ�\n", tclock, floor);
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
			//printf("��%ldʱ�̵������ڵ�%d��!\n", (double)(tclock*0.1), floor);
			for (int i = 0; i < number; i++)
				if (PassengerInElevator[i].GoFloor != floor)
					bs++;
			/*printf("%d,%d %d %d\n", floor, b[floor], bs, number);
			system("pause");*/
			if (b[floor] == 0 && bs == number)    //������û�ˣ�û����
			{
				add_t=add_time(add_t);
				//���ݲ����ţ������������½�
				int ofloor = floor;
				floor = Go(ts);      //�����ƶ�
				printf("��ǰʱ��%d		û����%d�����µ��ݣ����ݼ�������\n",tclock,ofloor);
			}
			else //����Ҫ������
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

int main()//������
{
	left.State = 0;                   //���ݳ�ʼ��
	left.Floor = 1;
	left.NumberofPerson = 0;
	Initialize();
	view(0,0);
	Run(&left);
	return 0;
}
