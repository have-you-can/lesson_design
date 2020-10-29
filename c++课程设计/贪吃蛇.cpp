#include<iostream> 
#include<windows.h> 
#include<conio.h> 
#include<time.h> 
#include<stdlib.h> 
#include<stdio.h>
using namespace std; 
const int N=21;
void Get_xy(int x,int y) //定位光标位置 
{ 
	HANDLE hout; 
	COORD pos; 
	pos.X=x*2; 
	pos.Y=y; 
	hout=GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleCursorPosition(hout,pos); 
} 
void Color(int num) //设置颜色 
{ 
	HANDLE hout; 
	hout=GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(hout,num); 
} 
void Initial() //初始化 
{ 
	int i,j; 
	int wall[N+2][N+2]={{0}}; 
	for(i=1;i<=N;i++) 
		for(j=1;j<=N;j++) 
			wall[i][j]=1; 
	Color(11); 
	for(i=0;i<N+2;i++) 
	{ 
		for(j=0;j<N+2;j++) 
		{ 
			if(wall[i][j]) 
				cout<<"■"; 
			else cout<<"□"; 
		} 
		cout<<endl;
	} 
	Get_xy(N+3,1); Color(20); 
	cout<<"按'W','S','A','D'进行操作"<<endl; 
	Get_xy(N+3,2); Color(20); 
	cout<<"按任意键暂停"<<endl; 
	Get_xy(N+3,3); Color(20); 
	cout<<"得分："<<endl; 
} 
void game() 
{ 
	int** snake=NULL; 
	int len=1; 
	int i; 
	int score=0; 
	int apple[2]; 
	int tail[2]; 
	char ch='p'; 
	Initial(); 
	srand((unsigned)time(NULL)); 
	apple[0]=rand()%N+1; 
	apple[1]=rand()%N+1; 
	Get_xy(apple[0],apple[-1]); 
	Color(12); 
	cout<<"●"<<endl; 
	snake=(int**)realloc(snake,sizeof(int*)*len); 
	for(i=0;i<len;i++) 
		snake[i]=(int*)malloc(sizeof(int)*2); 
	snake[0][0]=N/2; 
	snake[0][1]=N/2+1; 
	Get_xy(snake[0][0],snake[0][1]); Color(14); 
	cout<<"⊙"<<endl; 
	int flag=1; 
	while(1) 
	{ 
		if(flag) 
		{ 
			tail[0]=snake[len-1][0]; 
			tail[1]=snake[len-1][1]; 
			Get_xy(tail[0],tail[1]); 
			Color(11); 
			cout<<"■"<<endl; 
		} 
		flag=1; 
		for(i=len-1;i>0;i--)  
		{ 
			snake[i][0]=snake[i-1][0]; 
			snake[i][1]=snake[i-1][1]; 
			Get_xy(snake[i][0],snake[i][1]); 
			Color(14); 
			cout<<"★"<<endl; 
		} 
		if(_kbhit()) 
{ 
	
	ch=getch(); 
		}
		switch(ch) 
		{ 
		case 'W': 
		case 'w': snake[0][1]--; break; 
		case 'S': 
		case 's': snake[0][1]++; break; 
		case 'A': 
		case 'a': snake[0][0]--; break; 
		case 'D': 
		case 'd': snake[0][0]++; break; 
		default :break; 
		} 
		for(i=1;i<len;i++) 
		{ 
			if(snake[0][0]==snake[i][0] && snake[0][1]==snake[i][1]) 
			{ 
				Get_xy(N/2,N/2); Color(30); 
				cout<<"Game over!"<<endl; 
				exit(0); 
			} 
		} 
		Get_xy(snake[0][0],snake[0][1]); 
		Color(14); cout<<"⊙"<<endl; 
		Sleep(abs(200-0.5*score)); 
		if(snake[0][0]==apple[0] && snake[0][1]==apple[1]) 
		{ 
			flag=0; score++; len++; srand((unsigned)time(NULL)); 
			snake=(int**)realloc(snake,sizeof(int*)*len); 
			snake[len-1]=(int*)malloc(sizeof(int)*2); 
			Get_xy(N+6,3); Color(20); cout<<score<<endl; 
			apple[0]=rand()%N+1; apple[1]=rand()%N+1; 
			Get_xy(apple[0],apple[1]); 
			Color(12);  
			cout<<"●"<<endl; 
		} 
		if(snake[0][0]==-1 || snake[0][0]==N+1 || snake[0][1]==-1 || snake[0][1]==N+1) 
		{ 
			Get_xy(N/2,N/2); Color(30); 
			cout<<"Game Over!"<<endl; 
			for(i=0;i<len;i++) 
				free(snake[i]); 
			Sleep(INFINITE); 
			exit(0); 
		} 
		if(len>=N*N-1) 
		{ 
			Get_xy(N/2,N/2); Color(30); 
			cout<<"Win!"<<endl; 
			for(i=0;i<len;i++) 
				free(snake[i]); 
			Sleep(INFINITE); 
			exit(0); 
		} 
	} 
} 
int main() 
{ 
	game(); 
}
