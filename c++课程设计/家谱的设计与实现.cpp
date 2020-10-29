#include<stdio.h>
#include<Windows.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include<iostream>
using namespace std;
//设置光标位置
void gotoxy(int x,int y)                             
{ 
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos={x,y};
	SetConsoleCursorPosition(h,pos);
}
//定义家庭成员的结构体
typedef struct familymember member;
typedef struct familymember               
{
	member *lchild;
	member *rchild;
	char name[80];
	char sex[10];
	int n;
}member;
member *family;
//输出信息
void printmemb(member *p)
{
	printf("第%d代：名字是：%s 性别：%s\n",p->n,p->name ,p->sex );
}
//前序遍历
void protravel(member *p)
{
	printmemb(p);
	if(p->lchild )
		protravel(p->lchild );
	if(p->rchild)
		protravel(p->rchild);
}
//家庭成员的录入
//祖先的录入，建立家谱
void inputan(member *ancestor)
{
	ancestor->n =1;
	gotoxy(50,5);
	printf("请输入祖先(第一代)的名字和性别:");
	scanf("%s %s",&(ancestor->name),&ancestor->sex);
	fflush(stdin);
	ancestor->rchild =NULL;
	ancestor->lchild =NULL;
}
//家庭成员的录入，按父亲查找录入
member* search(member *p,char name[]);
void inputmeb(member *p)
{
	char nam[80];
	member *m,*n,*temp;
	m=(member*)malloc(sizeof(member));	
	printf("请输入要录入成员的父亲的名字:");
	scanf("%s",&nam);
	fflush(stdin);
	m=search(p,nam);
	while(m==NULL)
	{
		printf("查无此人！\n");
		printf("请重新输入要录入成员的父亲的名字:");
		scanf("%s",&nam);
		fflush(stdin);
		m=search(p,nam);
	}
	temp=(member*)malloc(sizeof(member));
		temp->lchild=temp->rchild=NULL;
		printf("请输入录入成员的名字:");
		scanf("%s",temp->name);
		n=search(p,temp->name);
		while(n!=NULL)
		{
			printf("请重新输入录入成员的名字:");
			scanf("%s",temp->name);
			n=search(p,temp->name);
		}
		printf("请输入录入成员的性别:");
		scanf("%s",temp->sex);

	if(m->lchild==NULL)
	{ 
		m->lchild=temp;
		m->lchild ->n =m->n +1;	
	}
	else if(m->rchild==NULL)
	{
		m->rchild=temp;
		m->rchild ->n =m->n +1;	
	}
	else
	{
		printf("对不起，不能再添加孩子了！\n");
	}
}
//家庭成员的修改
void change(member *p)
{
	member *m;
	char name[80];
	m=(member*)malloc(sizeof(member));
	printf("请输入要修改的成员的名字:");
	scanf("%s",&name);
	m=search(p,name);
	while(m==NULL)
	{
		printf("查无此人！");
		printf("请重新输入要修改的成员的名字:");
		scanf("%s",&name);
		m=search(p,name);
	}
	printf("请输入替换的的名字和性别:");
	scanf("%s %s",&m->name,&m->sex );
}
//家庭成员的查询
//通过前序遍历查询，并返回查找到的成员
member* search(member *p,char nam[])
{
	member *q;
	if(p==NULL || strcmp(p->name,nam)==0)//
		return p;
	else
	{
		q=search(p->lchild,nam);
		if(q!=NULL)
			return q;
		else
			return search(p->rchild,nam);
	}
}
void searchfor(member *m)
{
	char nam[80];
	member *m1;
	printf("请输入要查询的成员的姓名:");
	fflush(stdin);
	gets(nam);
	m1=search(m,nam);
	if(m1==NULL)
		printf("查无此人!");
	else 
		printmemb(m1);
}
void main()
{
	char select;
	int i=10;
	family=(member*)malloc(sizeof(member));
	family->lchild=family->rchild=NULL;
	while(1)
	{
		//菜单
		gotoxy(50,4);
		printf("0.家族祖先的录入。");
		gotoxy(50,5);
		printf("1.家族成员的录入。");
		gotoxy(50,6);
		printf("2.家庭成员的修改。");
		gotoxy(50,7);
		printf("3.家族成员的查询。");
		gotoxy(50,8);
		printf("4.家族成员的排序。");
		gotoxy(24,9);
		printf("请输入你所要进行的操作序号:");
		cin>>select;
		while((select-'0')!=0&&(select-'0')!=2&&(select-'0')!=3&&(select-'0')!=4&&(select-'0')!=1)
		{
			gotoxy(24,i++);
			cout<<"输入错误，请重新输入:";
			cin>>select;
			getchar();
		}
		system("cls");
		switch(select-'0')
		{
		case 0:
			inputan(family);
			system("pause");
			break;
		case 1:
			inputmeb(family);
			system("pause");
			break;
		case 2:change(family);
			system("pause");
			break;
		case 3:searchfor(family);
			system("pause");
			break;
		case 4:protravel(family);
			system("pause");
			break;
		}
		system("cls");
	}
	free(family);
}
