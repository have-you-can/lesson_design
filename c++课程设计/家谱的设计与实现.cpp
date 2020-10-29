#include<stdio.h>
#include<Windows.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include<iostream>
using namespace std;
//���ù��λ��
void gotoxy(int x,int y)                             
{ 
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos={x,y};
	SetConsoleCursorPosition(h,pos);
}
//�����ͥ��Ա�Ľṹ��
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
//�����Ϣ
void printmemb(member *p)
{
	printf("��%d���������ǣ�%s �Ա�%s\n",p->n,p->name ,p->sex );
}
//ǰ�����
void protravel(member *p)
{
	printmemb(p);
	if(p->lchild )
		protravel(p->lchild );
	if(p->rchild)
		protravel(p->rchild);
}
//��ͥ��Ա��¼��
//���ȵ�¼�룬��������
void inputan(member *ancestor)
{
	ancestor->n =1;
	gotoxy(50,5);
	printf("����������(��һ��)�����ֺ��Ա�:");
	scanf("%s %s",&(ancestor->name),&ancestor->sex);
	fflush(stdin);
	ancestor->rchild =NULL;
	ancestor->lchild =NULL;
}
//��ͥ��Ա��¼�룬�����ײ���¼��
member* search(member *p,char name[]);
void inputmeb(member *p)
{
	char nam[80];
	member *m,*n,*temp;
	m=(member*)malloc(sizeof(member));	
	printf("������Ҫ¼���Ա�ĸ��׵�����:");
	scanf("%s",&nam);
	fflush(stdin);
	m=search(p,nam);
	while(m==NULL)
	{
		printf("���޴��ˣ�\n");
		printf("����������Ҫ¼���Ա�ĸ��׵�����:");
		scanf("%s",&nam);
		fflush(stdin);
		m=search(p,nam);
	}
	temp=(member*)malloc(sizeof(member));
		temp->lchild=temp->rchild=NULL;
		printf("������¼���Ա������:");
		scanf("%s",temp->name);
		n=search(p,temp->name);
		while(n!=NULL)
		{
			printf("����������¼���Ա������:");
			scanf("%s",temp->name);
			n=search(p,temp->name);
		}
		printf("������¼���Ա���Ա�:");
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
		printf("�Բ��𣬲�������Ӻ����ˣ�\n");
	}
}
//��ͥ��Ա���޸�
void change(member *p)
{
	member *m;
	char name[80];
	m=(member*)malloc(sizeof(member));
	printf("������Ҫ�޸ĵĳ�Ա������:");
	scanf("%s",&name);
	m=search(p,name);
	while(m==NULL)
	{
		printf("���޴��ˣ�");
		printf("����������Ҫ�޸ĵĳ�Ա������:");
		scanf("%s",&name);
		m=search(p,name);
	}
	printf("�������滻�ĵ����ֺ��Ա�:");
	scanf("%s %s",&m->name,&m->sex );
}
//��ͥ��Ա�Ĳ�ѯ
//ͨ��ǰ�������ѯ�������ز��ҵ��ĳ�Ա
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
	printf("������Ҫ��ѯ�ĳ�Ա������:");
	fflush(stdin);
	gets(nam);
	m1=search(m,nam);
	if(m1==NULL)
		printf("���޴���!");
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
		//�˵�
		gotoxy(50,4);
		printf("0.�������ȵ�¼�롣");
		gotoxy(50,5);
		printf("1.�����Ա��¼�롣");
		gotoxy(50,6);
		printf("2.��ͥ��Ա���޸ġ�");
		gotoxy(50,7);
		printf("3.�����Ա�Ĳ�ѯ��");
		gotoxy(50,8);
		printf("4.�����Ա������");
		gotoxy(24,9);
		printf("����������Ҫ���еĲ������:");
		cin>>select;
		while((select-'0')!=0&&(select-'0')!=2&&(select-'0')!=3&&(select-'0')!=4&&(select-'0')!=1)
		{
			gotoxy(24,i++);
			cout<<"�����������������:";
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
