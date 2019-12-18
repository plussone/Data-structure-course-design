#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

typedef struct BSTNode
{
	string imt[5];            //专业、班级、学号姓名
	struct BSTNode* lchild, * rchild;
}BSTNode, * BSTree;

struct Node
{
	string imt[5];
}Student[100];

string new_imt[5];       //输入的学生信息
string cszyw = "测试样例占用位";
int n; //学生人数

ofstream fout;

void MainMenu()    //主菜单
{
	printf("...............欢迎使用学籍管理系统...............\n");
	printf("...............    1.增加信息      ...............\n");
	printf("...............    2.删除信息      ...............\n");
	printf("...............    3.修改信息      ...............\n");
	printf("...............    4.查找信息      ...............\n");
	printf("...............    0.退出系统      ...............\n");
}

int czhs(BSTree& T, string new_imt,BSTree f,BSTree& p,int n) //查找函数
{
	if (!T)
	{
		p = f;
		return 0;
	}
	else if (new_imt == cszyw)
	{
		 if (T->imt[n] > new_imt)
		{
			return czhs(T->rchild, new_imt, T, p, n);
		}
		else
		{
			return czhs(T->lchild, new_imt, T, p, n);
		}
	}
	else if (new_imt == T->imt[n])
	{
		p = T;
		//int a = T->imt[0].length();
		return 1;
	}
	else if (T->imt[n] > new_imt)
	{
		return czhs(T->rchild, new_imt,T,p,n);
	}
	else
	{
		return czhs(T->lchild, new_imt,T,p,n);
	}
}

void czhs_dg(BSTree& T,BSTree& p, BSTree& s) //查找无效节点函数
{
	if (T)
	{
		if (T->lchild == p||T->rchild == p)
		{
			s = T;
			return ;
		}
		if (T->lchild)
			czhs_dg(T->lchild,p,s);
		if (T->rchild)
			czhs_dg(T->rchild,p,s);
	}
}

int czxy(BSTree& T,string new_imt,BSTree& p) //查找学院函数
{
	int a = 0;
	if (T)
	{
		if (T->imt[0] == new_imt)
		{
			p = T;
			return 1;
		}
		if (czxy(T->lchild, new_imt, p))
		{
			return 1;
		}
		if (czxy(T->rchild, new_imt, p))
		{
			return 1;
		}
	} 
	return 0;
}

void node_stu(BSTree T) //生成学生结构体数组
{
	if (T)
	{
		Student[n].imt[0] = T->imt[0];
		Student[n].imt[1] = T->imt[1];
		Student[n].imt[2] = T->imt[2];
		n++;
		if (T->lchild)
			node_stu(T->lchild);
		if (T->rchild)
			node_stu(T->rchild);
	}
}

int cmp(Node a,Node b) //学生结构体数组排序函数
{
	if (a.imt[0] > b.imt[0])
	{
		return 1;
	}
	else if (a.imt[0] == b.imt[0]&&a.imt[1]>b.imt[1])
	{
		return 1;
	}
	else if (a.imt[0] == b.imt[0] && a.imt[1] == b.imt[1] && a.imt[2] > b.imt[2])
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void wite(int n) //打印空白函数
{
	while (n--)
	{
		printf(" ");
	}
}

void Output(BSTree& T)  //采用中序遍历的方式输出信息
{
	printf("杭电\n");
	if (T)
	{
		string a="", b="", c="";
		n = 0;
		node_stu(T);
		sort(Student, Student + n, cmp);
		for (int i = 0; i < n;i++)
		{
			if (Student[i].imt[0] != a)
			{
				if (Student[i].imt[0] == cszyw)
				{
					printf("\n");
				}
				else
				{
					wite(4);
					cout << "->" + Student[i].imt[0] << endl;
					if (Student[i].imt[1] == cszyw)
					{
						printf("\n");
					}
					else
					{
						wite(6 + Student[i].imt[0].length());
						cout << "->" + Student[i].imt[1] << endl;
						if (Student[i].imt[2] == cszyw)
						{
							printf("\n");
						}
						else
						{
							wite(8 + Student[i].imt[0].length() + Student[i].imt[1].length());
							cout << "->" + Student[i].imt[2] << endl;
						}
					}
				}
			}
			else if(Student[i].imt[1] != b)
			{
				if (Student[i].imt[1] == cszyw)
				{
					printf("\n");
				}
				else
				{
					wite(6 + Student[i].imt[0].length());
					cout << "->" + Student[i].imt[1] << endl;
					if (Student[i].imt[2] == cszyw)
					{
						printf("\n");
					}
					else
					{
						wite(8 + Student[i].imt[0].length() + Student[i].imt[1].length());
						cout << "->" + Student[i].imt[2] << endl;
					}
				}
			}
			else if(Student[i].imt[2] != c)
			{
				if (Student[i].imt[2] == cszyw)
				{
					printf("\n");
				}
				else
				{
					wite(8 + Student[i].imt[0].length() + Student[i].imt[1].length());
					cout << "->" + Student[i].imt[2] << endl;
				}
			}
			a = Student[i].imt[0];
			b = Student[i].imt[1];
			c = Student[i].imt[2];
		}
	}
}

void Out_dg(BSTree& T) //打印单个学生信息
{
	printf("杭电\n");
	if (T)
	{
		if (T->imt[0] == cszyw)
		{
			printf("\n");
		}
		else
		{
			wite(4);
			cout << "->" + T->imt[0] << endl;
			if (T->imt[1] == cszyw)
			{
				printf("\n");
			}
			else
			{
				wite(6 + T->imt[0].length());
				cout << "->" + T->imt[1] << endl;
				if (T->imt[2] == cszyw)
				{
					printf("\n");
				}
				else
				{
					wite(8 + T->imt[0].length() + T->imt[1].length());
					cout << "->" + T->imt[2] << endl;
				}
			}
		}
	}				
}

int InsertBSTree(BSTree& T, string a, string b, string c)  //在二叉排序树中插入节点
{
	BSTree f, p;
	f = p = NULL;
	if (!czhs(T, c, f, p, 2))
	{
		BSTree s = new BSTNode;
		s->imt[2] = c;
		s->imt[1] = b;
		s->imt[0] = a;
		s->lchild = s->rchild = NULL;
		if (!p)
		{
			T = s;
			T->lchild = T->rchild = NULL;
		}
		else if (p->imt[2] > s->imt[2])
		{
			p->rchild = s;
		}
		else
		{
			p->lchild = s;
		}
	}
	return 1;
}

void xghs(BSTree& T) //修改函数
{
	int num = 0;
	BSTree f, p;
	f = p = NULL;
	printf("请选择要进行的操作的对象:\n1.学生 2.学院 3.班级 0.返回\n");
	scanf("%d", &num);
	switch(num)
	{	
		case 1:
		{	
			n = 0;
			int flag = 0;
			node_stu(T);
			printf("请输入要修改的学生学号和姓名:");
			cin >> new_imt[2];
			for(int i =0;i<n;i++)
			{
				if (Student[i].imt[2] == new_imt[2])
				{
					flag = 1;
					printf("请输入正确的学生学号和姓名:");
					cin >> new_imt[2];
					Student[i].imt[2] = new_imt[2];
					delete T;
					T = NULL;
					for (int i = 0; i < n; i++)
					{
						InsertBSTree(T, Student[i].imt[0], Student[i].imt[1], Student[i].imt[2]);
					}
					break;
				}
			}
			if(!flag)
			{
				printf("查无此人\n");
			}
			break;
		}
		case 2:
		{
			int n = 0;
			string new_xy;
			printf("请输入要修改的学院:");
			cin >> new_imt[0];
			printf("请输入正确的学院:");
			cin >> new_xy;
			while(czxy(T, new_imt[0], p))
			{
				n++;
				p->imt[0] = new_xy;
			}
			if(!n)
			{
				printf("查无此学院\n");
			}
			break;
		}
		case 3:
		{
			int n = 0;
			string new_bj;
			printf("请输入要修改班级的学院:");
			cin >> new_imt[0];
			printf("请输入要修改的班级:");
			cin >> new_imt[1];
			printf("请输入正确的班级:");
			cin >> new_bj;
			while (czxy(T, new_imt[0], p))
			{
				if (p->imt[1] == new_imt[1])
				{
					n++;
					p->imt[1] = new_bj;	
				}
				p->imt[0] = cszyw;
			}
			if (!n)
			{
				printf("查无此班级\n");
			}
			while (czxy(T, cszyw, p))
			{
				p->imt[0] = new_imt[0];
			}
			break;
		}
		default:
		{
			if (num)
			{
				printf("输入错误（错误代码：02）\n");
			}
			return ;
		}
	}
	return ;
}

int Delete(BSTree& T,BSTree& p)  //寻找对应的节点并删除
{
	int flag = 0;
	BSTree q, s;
	q = s = NULL;
	if (!p->lchild && !p->rchild)
	{
		czhs_dg(T,p,s);
		if (s == NULL)
		{
			T = s;
		}
		else if (s->lchild == p)
		{
			s->lchild = NULL;
		}
		else
		{
			s->rchild = NULL;
		}
	}
	else if (!p->rchild)
	{
		q = p->lchild;
		*p = *p->lchild;
		delete(q);
	}
	else if (!p->lchild)
	{
		q = p->rchild;
		*p = *p->rchild;
		delete(q);
	}
	else
	{
		q = p;
		s = p->lchild;
		while (s->rchild)
		{
			q = s;
			s = s->rchild;
		}
		q->rchild = s->lchild;
		s->rchild = p->rchild;
		s->lchild = p->lchild;
		*p = *s;
		delete(s);
	}
	return 1;
}

int DeleteBST(BSTree& T)  //删除信息
{
	int num = 0;
	BSTree f, p;
	f = p = NULL;
	printf("请选择要进行的操作的对象:\n1.学生 2.学院 3.班级 0.返回\n");
	scanf("%d", &num);
	if (!T)
		return 0;
	switch(num)
	{
		case 1:
		{
			printf("请输入要删除的学生的学号姓名:");
			cin >> new_imt[2];
			if (czhs(T, new_imt[2], f, p, 2))
			{
				Delete(T,p);
			}
			break;
		}
		case 2:
		{
			printf("请输入要删除的学院:");
			cin >> new_imt[0];
			while (czxy(T, new_imt[0], p))
			{
				Delete(T,p);
			}
			break;
		}
		case 3:
		{
			printf("请输入要删除班级的学院:");
			cin >> new_imt[0];
			printf("请输入要删除的班级:");
			cin >> new_imt[1];
			while (czxy(T, new_imt[0], p))
			{
				if (p->imt[1] == new_imt[1])
				{
					Delete(T,p);
				}
				p->imt[0] = cszyw;
			}
			while (czxy(T, cszyw, p))
			{
				p->imt[0] = new_imt[0];
			}
			break;
		}
		default:
		{
			if (num)
			{
				printf("输入错误（错误代码：02）\n");
			}
			return 2;
		}
	}
	return 1;
}

int Inserts(BSTree& T) //增加单位函数
{
	int num = 0;
	BSTree f, p;
	f = p = NULL;
	printf("请选择要进行的操作的对象:\n1.学生 2.学院 3.班级 0.返回\n");
	scanf("%d", &num);
	if (!T)
		return 0;
	switch (num)
	{
		case 1:
		{
			printf("请输入学院:");
			cin >> new_imt[0];
			printf("请输入班级:");
			cin >> new_imt[1];
			printf("请输入学号及姓名:");
			cin >> new_imt[2];
			if (czhs(T, new_imt[2], f, p, 2))
			{
				printf("添加失败，已存在该学生\n");
			}
			else
			{
				InsertBSTree(T, new_imt[0], new_imt[1], new_imt[2]);
			}
			break;
		}
		case 2:
		{
			printf("请输入要增加的学院:");
			cin >> new_imt[0];
			if(czxy(T, new_imt[0], p))
			{
				printf("添加失败，已存在该学院\n");
			}
			else
			{
				InsertBSTree(T, new_imt[0],cszyw,cszyw);
			}
			break;
		}
		case 3:
		{
			int flag = 1;
			printf("请输入要增加班级的学院:");
			cin >> new_imt[0];
			printf("请输入要增加的班级:");
			cin >> new_imt[1];
			while (czxy(T, new_imt[0], p))
			{
				if (p->imt[1] == new_imt[1])
				{
					flag = 0;
					printf("添加失败，已存在该班级\n");
					break;
				}
				p->imt[0] = cszyw;
			}
			while (czxy(T, cszyw, p))
			{
				p->imt[0] = new_imt[0];
			}
			if (flag)
			{
				InsertBSTree(T, new_imt[0], new_imt[1], cszyw);
			}
			break;
		}
		default:
		{
			if (num)
			{
				printf("输入错误（错误代码：02）\n");
			}
			return 2;
		}
	}
	return 1;
}

void close(BSTree& T) //关闭储存函数
{
	if (T)
	{
		fout << T->imt[0] << endl;
		fout << T->imt[1] << endl;
		fout << T->imt[2] << endl;
		if (T->lchild)
			close(T->lchild);
		if (T->rchild)
			close(T->rchild);
	}
}

int main()
{
	int n;
	BSTree T = NULL;
	BSTree f = NULL, p = NULL;
	string a, b, c;
	MainMenu();
	ifstream fin;
	fin.open(".\\data.txt");
	while (getline(fin, a) && getline(fin, b) && getline(fin, c))
	{
		InsertBSTree(T, a, b, c);
	}
	fin.close();
	Output(T);
	while (printf("1.增加信息 2.删除信息 3.修改信息 4.查找信息 0.退出系统\n")&&scanf("%d", &n)&&n)
	{			
		switch (n)
		{
			case 1:
			{
				Inserts(T);
				Output(T);
				break;
			}
			case 2:
			{
				DeleteBST(T);
				Output(T);
				break;
			}
			case 3:
			{
				xghs(T);
				Output(T);
				break;
			}
			case 4:
			{
				printf("请输入查找的学生的学号姓名:");
				cin >> new_imt[2];
				if (!czhs(T, new_imt[2], f, p, 2))
				{
					printf("查无此人\n");
				}
				Out_dg(p);
				break;
			}
		}
	}	
	fout.open(".\\data.txt");
	close(T);
	fout.close();	
	return 0;
}
