#pragma warning(disable:4996);
/*Man Down*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include <windows.h>
#include <stdbool.h>
#include <math.h>
#include <graphics.h>                   //图形库
#include <conio.h>                      //图形库

/*****************************控制台颜色函数宏定义*****************************/
#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED)
#define GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN)
#define BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE)
#define GREENPLUS SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define REDPLUS SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY)
#define BLUEPLUS SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY)
#define YELLO SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE)
#define INDIG SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define MagentaPlus SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define White SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY)
#define Other SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED&FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY)

/*长宽大小*/
#define MAX 20
#define BoardLEN 5 

/*踏板类型宏定义数值*/
#define Sinpe 0
#define Hard 1
#define Fragile 2
#define Move 3
#define HP_PLUS 4 
#define JUMP 5

void HideCursor(void); 						/*隐藏光标*/
void Start(void);                       			/*开始选择*/
void gotoxy(int, int);						/*移动光标*/
bool Menu(void);
bool Menu2(void);                         /*选择菜单*/
void Begin(void);						/*初始化场景*/
void RandBoard(int);						/*随机生成踏板*/
void Play(void);						/*玩家操作*/
void Display(void); 						/*显示*/
unsigned int FindMax(void);					/*找出最下面的踏板的y坐标*/
bool ManMoveDetectionA(void);					/*是否进行移动的检测*/
bool ManMoveDetectionD(void);
bool CoordinateComparisonOfMoving(void);			/*碰撞踏板的检测*/
int CollisionDetection(void);					/*踩踏碰撞检测*/
void GenerationDetection(void);					/*生成踏板函数*/
void SomethingWillHappen(int);					/*踩踏板事件生成*/
bool IsDieDetection(void); 					/*死亡检测*/
int rank();                              /*将分数写入排行榜*/
int readrank();                           /*读出排行榜*/

int HP = 100;        /*生命*/
int Score = 0;		 /*分数*/
int Times_ = 0;
unsigned long Speed = 400 + 0.1 * Times_;

/*分数储存*/
typedef struct inf
{
	char name[20];
	int score;
}info;

/*人物位置信息*/
struct MAN
{
	unsigned int x;//正整数
	unsigned int y;
	bool Stop;//true or faulse
}Man;

/*游戏场景中的踏板*/
struct BOARD
{
	unsigned int leftx;
	unsigned int rightx;
	unsigned int y;
	int style;
}Board[5];

int main(void)
{
	HideCursor();
	Start();
	srand((unsigned)(time(0)));         //是随机数发生器的初始化函数
	Begin();
	Play();
	Menu();
	rank();
	while (Menu2)
	{
		srand((unsigned)(time(0)));
		Begin();
		Play();
		Menu();
		rank();
	}
	return 0;
}

void Start(void)
{
	printf("\n\n\n\n\n\n");
	printf("\t ________________________________________________________________\n");
	printf("\t|                                                                |\n");
	printf("\t|                                                                |\n");
	printf("\t|                                                                |\n");
	printf("\t|                                                                |\n");
	printf("\t|                                                                |\n");
	printf("\t|                                                                |\n");
	printf("\t|                 welcome to the game                            |\n");
	printf("\t|                 按任意键开始游戏                               |\n");
	printf("\t|                                                                |\n");
	printf("\t|                                                                |\n");
	printf("\t|                                                                |\n");
	printf("\t|                                                                |\n");
	printf("\t|                                                                |\n");
	printf("\t|________________________________________________________________|\n");
	system("pause");
	system("cls");

	char ch;
	int speed_temp;

	printf("***********************下一百层***********************\n\n");
	printf("                     a.开始游戏.\n");
	printf("                     b.玩法介绍.\n");
	printf("                     c.设置难度.\n");
	printf("                      d.排行榜. \n");

N:
	scanf_s("%c", &ch);
	switch (ch)
	{
	case 'B':
	case 'b':
	{
		system("cls");
		printf("方向控制:  ←:A  →:D    \n\n");
		printf("石板种类:\n");
		REDPLUS;
		printf("^^^^^^");
		printf("  尖刺\n\n");
		BLUEPLUS;
		printf("------");
		printf("  普通石板\n\n");
		YELLO;
		printf("~~~~~~");
		printf("  易碎石板\n\n");
		White;
		printf("******");
		printf("  传送带\n\n");
		GREENPLUS;
		printf("++++++");
		printf("  加血石板\n\n");
		YELLOW;
		printf("######");
		printf("  弹跳石板\n\n");
		printf("玩法: 上层尖刺不断向下移动，玩家通过控制人物，避免被尖刺扎伤，又要避免掉入深渊。\n");

		getchar();
		getchar();
		break;
	}
	case 'A':
	case 'a':
		return;
		break;
	case 'C':
	case 'c':
	{
		do
		{
			printf("请输入速度等级（1—10）:\n");/*gai1*/
			scanf_s("%d", &speed_temp);
			printf("");
		} while (speed_temp < 0);
		Speed = (unsigned int)(speed_temp);
		break;
	}
	case 'D':
	case 'd':
	{
		int readrank();//读出排行榜
		break;
	}
	default:
		goto N;
		break;
	}
	return;
}
/**
* 游戏结束之后的菜单选择.
*/

bool Menu(void)
{
	char ch;
	White;
	system("cls");
	printf("游戏结束！\n得分:%d\n\n", Score);
	printf("累计石板生成次数:%d\n\n", Times_ + 4);
	return 0;
}

/**
* 初始化一些游戏场景数据.
*/

void Begin(void)
{
	Man.x = 5;
	Man.y = 5;
	Man.Stop = false;
	RandBoard(0);
	Board[0].y = 1;
	RandBoard(1);
	Board[1].y = 5;
	RandBoard(2);
	Board[2].y = 9;
	RandBoard(3);
	Board[3].y = 13;
	RandBoard(4);
	Board[4].y = 17;
	Times_++;
}


/**
* 随机生成一个“石板”信息填充到指定结构.
* @N 被填充结构的下标.
*/
void RandBoard(int N)
{
	do
	{
		Board[N].leftx = rand() % MAX;
		Board[N].rightx = Board[N].leftx + (BoardLEN - 1);
	} 
	while (Board[N].rightx > MAX);
	
		Board[N].style = rand() % 6;
		Board[N].y = FindMax() + 4;
	
	Times_++;
}

/**
* 检测玩家是否站到了石板上，如果是，在Man结构中的Stop标记为true.
* @return 如果是，返回该石板结构下标.如果不是，返回-1.
*/

int CollisionDetection(void)
{
	int x, y, num;
	for (x = 0; x < MAX; x++)
	{
		for (y = 0; y < MAX; y++)
		{
			for (num = 0; num < 5; num++)
			{
				if (Man.y + 2 == Board[num].y || Man.y + 1 == Board[num].y)
				{
					if (Man.x + 2 >= Board[num].leftx && Man.x <= Board[num].rightx)
					{
						Man.Stop = true;
						return num;
					}
				}
			}
		}
	}
	Man.Stop = false;
	return -1;
}

void Play(void)
{
	char ch;
	int num; 					/*获取玩家正在站立的木板的位置*/
	unsigned int count = 0;
	while (1)
	{
		while (_kbhit())
		{
			ch = _getch();
			switch (ch)
			{
			case 'a':
			case 'A':
			{
				if (!ManMoveDetectionA())
				{
					Man.x--;
				}
				break;
			}
			case 'd':
			case 'D':
			{
				if (!ManMoveDetectionD())
				{
					Man.x++;
				}
				break;
			}
			case'p':
			case'P':
			{
				system("pause");
			}
			}
		}
		system("cls");
		GenerationDetection();
		num = CollisionDetection();
		SomethingWillHappen(num);
		for (count = 0; count < 5; count++)
		{
			Board[count].y--;
		}
		if (!Man.Stop)
		{
			(Man.y)++;
		}
		else
		{
			Man.y = Board[num].y - 1;

		}

		if (IsDieDetection())
		{
			return;
		}
		Display();
		Score++;
		Sleep(Speed);//延时函数
	}

	return;
}


/*
显示游戏场景.
*/

void Display(void)
{
	int N;
	gotoxy(Man.x + 10, Man.y + 1);
	White;
	printf("★");
	gotoxy(20 + 10, 0 + 1);
	printf("HP:%d", HP);
	gotoxy(20 + 10, 1 + 1);
	printf("Score:%d", Score);
	gotoxy(20 + 10, 2 + 1);
	printf("p/P:暂停");
	gotoxy(10, MAX + 1);
	INDIG;
	printf("---------------");
	gotoxy(10, 0);
	White;
	printf("^^^^^^^^^^^^^^^");
	for (N = 0; N < 5; N++)
	{
		if (Board[N].y > MAX)
		{
			continue;
		}
		gotoxy(Board[N].leftx + 10, Board[N].y + 1);
		switch (Board[N].style)
		{
		case Sinpe:
		{
			REDPLUS;
			printf("^^^^^^");
			break;
		}
		case Hard:
		{
			BLUEPLUS;
			printf("------");
			break;
		}
		case Fragile:
		{
			YELLOW;
			printf("~~~~~~");
			break;
		}
		case Move:
		{
			White;
			printf("******");
			break;
		}
		case HP_PLUS:
		{
			GREENPLUS;
			printf("++++++");
			break;
		}
		case JUMP:
		{
			YELLOW;
			printf("######");
			break;
		}
		}
	}
}

/*控制左右移动*/
bool ManMoveDetectionA(void)
{
	return (Man.x > 0 && CoordinateComparisonOfMoving());
}

bool ManMoveDetectionD(void)
{
	return (Man.x > 0 && CoordinateComparisonOfMoving());
}

/*判定人物左右移动*/
bool CoordinateComparisonOfMoving(void)
{
	int x, y, num;
	for (x = 0; x < MAX; x++)
	{
		for (y = 0; y < MAX; y++)
		{
			for (num = 0; num < 5; num++)
			{
				if (Man.x == Board[num].leftx && Man.y == Board[num].y)
				{
					return true;
				}
				else if (Man.x == Board[num].rightx && Man.y == Board[num].y)
				{
					return true;

				}
			}
		}
	}
	return false;
}

/*控制砖块生成*/
void GenerationDetection(void)
{
	int count;
	for (count = 0; count < 5; count++)
	{
		if (Board[count].y == 0)
		{
			RandBoard(count);
			return;
		}
	}
	return;
}

unsigned int FindMax(void)
{
	unsigned int Tmp, Tmp2, Tmp3, Tmp4;
	Tmp = max(Board[0].y, Board[1].y);
	Tmp2 = max(Board[2].y, Board[3].y);
	Tmp3 = max(Board[4].y, Board[3].y);/*gai*/
	Tmp4 = max(Tmp, Tmp2);
	return max(Tmp3, Tmp4);
}

void SomethingWillHappen(int num)
{
	if (num >= 0)
	{
		switch (Board[num].style)
		{
		case Sinpe:
		{
			HP -= 20;
			break;
		}
		case Fragile:
		{
			RandBoard(num);
			Man.Stop = false;
			break;
		}
		case Move:
		{
			if (Man.x <= 10)
			{
				Man.x++;
			}
			else
				Man.x--;
			break;
		}
		case HP_PLUS:
		{
			HP += 10;
			if (HP > 100)
			{
				HP = 100;
			}
			break;
		}
		case JUMP:
		{
			Man.y = (Man.y) - 2;

			break;
		}
		}
	}
}

bool IsDieDetection(void)
{
	if (HP <= 0 || Man.y <= 0 || Man.y >= MAX)
	{
		return true;
	}
	return false;
}

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
	return;
}

void HideCursor(void)
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

int rank()
{
	info tmp;
	FILE *fp;
	printf("大侠请输入您的大名：");
	scanf_s("%s", &tmp.name);
	tmp.score = Score;
	fp = fopen("rank.txt", "a");
	if (fp == NULL)
	{
		printf("cannot open the files\n");
		system("pause");
		return -1;//如果文件出现错误返回-1  
	}
	fprintf(fp, "%s %d", tmp.name, tmp.score);
	fclose(fp);
	return Menu2();
}

int readrank()
{
	info tmp[10];
	info temp;
	int n = 0, j = 0, i = 0, k = 0;
	FILE *fp;
	fp = fopen("rank.txt", "rb");
	if (fp == NULL)
	{
		printf("cannot open the files\n");
		system("pause");
		return -1;
	}
	for (i = 0; i < n - 1; i++)//采用冒泡法进行排序 
	{
		k = i;
		for (j = i + 1; j < n; j++)
			if (tmp[j].score > tmp[k].score)//排序比较大小  
				k = j;
		temp = tmp[k];
		tmp[k] = tmp[i];
		tmp[i] = temp;//当符合条件时进行数据交换
	}
	i = 0;
	while (i <= 10 && fscanf(fp, "%s%d", tmp[i].name, &tmp[i].score) != EOF)
	{
		printf("%3d%15s%10d\n", i + 1, tmp[i].name, tmp[i].score);
		i++;
	}
	fclose(fp);
	return 0;
}

bool Menu2(void)
{
	char ch;
	printf("\n\n继续游戏？(Y键继续,其余任意键退出):");
	scanf_s("%c", &ch);
	return (ch == 'Y' || ch == 'y');
}
