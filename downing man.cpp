#pragma warning(disable:4996);
/*Man Down*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include <windows.h>
#include <stdbool.h>
#include <math.h>
#include <graphics.h>                   //ͼ�ο�
#include <conio.h>                      //ͼ�ο�

/*****************************����̨��ɫ�����궨��*****************************/
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

/*�����С*/
#define MAX 20
#define BoardLEN 5 

/*̤�����ͺ궨����ֵ*/
#define Sinpe 0
#define Hard 1
#define Fragile 2
#define Move 3
#define HP_PLUS 4 
#define JUMP 5

void HideCursor(void); 						/*���ع��*/
void Start(void);                       			/*��ʼѡ��*/
void gotoxy(int, int);						/*�ƶ����*/
bool Menu(void);
bool Menu2(void);                         /*ѡ��˵�*/
void Begin(void);						/*��ʼ������*/
void RandBoard(int);						/*�������̤��*/
void Play(void);						/*��Ҳ���*/
void Display(void); 						/*��ʾ*/
unsigned int FindMax(void);					/*�ҳ��������̤���y����*/
bool ManMoveDetectionA(void);					/*�Ƿ�����ƶ��ļ��*/
bool ManMoveDetectionD(void);
bool CoordinateComparisonOfMoving(void);			/*��ײ̤��ļ��*/
int CollisionDetection(void);					/*��̤��ײ���*/
void GenerationDetection(void);					/*����̤�庯��*/
void SomethingWillHappen(int);					/*��̤���¼�����*/
bool IsDieDetection(void); 					/*�������*/
int rank();                              /*������д�����а�*/
int readrank();                           /*�������а�*/

int HP = 100;        /*����*/
int Score = 0;		 /*����*/
int Times_ = 0;
unsigned long Speed = 400 + 0.1 * Times_;

/*��������*/
typedef struct inf
{
	char name[20];
	int score;
}info;

/*����λ����Ϣ*/
struct MAN
{
	unsigned int x;//������
	unsigned int y;
	bool Stop;//true or faulse
}Man;

/*��Ϸ�����е�̤��*/
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
	srand((unsigned)(time(0)));         //��������������ĳ�ʼ������
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
	printf("\t|                 ���������ʼ��Ϸ                               |\n");
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

	printf("***********************��һ�ٲ�***********************\n\n");
	printf("                     a.��ʼ��Ϸ.\n");
	printf("                     b.�淨����.\n");
	printf("                     c.�����Ѷ�.\n");
	printf("                      d.���а�. \n");

N:
	scanf_s("%c", &ch);
	switch (ch)
	{
	case 'B':
	case 'b':
	{
		system("cls");
		printf("�������:  ��:A  ��:D    \n\n");
		printf("ʯ������:\n");
		REDPLUS;
		printf("^^^^^^");
		printf("  ���\n\n");
		BLUEPLUS;
		printf("------");
		printf("  ��ͨʯ��\n\n");
		YELLO;
		printf("~~~~~~");
		printf("  ����ʯ��\n\n");
		White;
		printf("******");
		printf("  ���ʹ�\n\n");
		GREENPLUS;
		printf("++++++");
		printf("  ��Ѫʯ��\n\n");
		YELLOW;
		printf("######");
		printf("  ����ʯ��\n\n");
		printf("�淨: �ϲ��̲��������ƶ������ͨ������������ⱻ������ˣ���Ҫ���������Ԩ��\n");

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
			printf("�������ٶȵȼ���1��10��:\n");/*gai1*/
			scanf_s("%d", &speed_temp);
			printf("");
		} while (speed_temp < 0);
		Speed = (unsigned int)(speed_temp);
		break;
	}
	case 'D':
	case 'd':
	{
		int readrank();//�������а�
		break;
	}
	default:
		goto N;
		break;
	}
	return;
}
/**
* ��Ϸ����֮��Ĳ˵�ѡ��.
*/

bool Menu(void)
{
	char ch;
	White;
	system("cls");
	printf("��Ϸ������\n�÷�:%d\n\n", Score);
	printf("�ۼ�ʯ�����ɴ���:%d\n\n", Times_ + 4);
	return 0;
}

/**
* ��ʼ��һЩ��Ϸ��������.
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
* �������һ����ʯ�塱��Ϣ��䵽ָ���ṹ.
* @N �����ṹ���±�.
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
* �������Ƿ�վ����ʯ���ϣ�����ǣ���Man�ṹ�е�Stop���Ϊtrue.
* @return ����ǣ����ظ�ʯ��ṹ�±�.������ǣ�����-1.
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
	int num; 					/*��ȡ�������վ����ľ���λ��*/
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
		Sleep(Speed);//��ʱ����
	}

	return;
}


/*
��ʾ��Ϸ����.
*/

void Display(void)
{
	int N;
	gotoxy(Man.x + 10, Man.y + 1);
	White;
	printf("��");
	gotoxy(20 + 10, 0 + 1);
	printf("HP:%d", HP);
	gotoxy(20 + 10, 1 + 1);
	printf("Score:%d", Score);
	gotoxy(20 + 10, 2 + 1);
	printf("p/P:��ͣ");
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

/*���������ƶ�*/
bool ManMoveDetectionA(void)
{
	return (Man.x > 0 && CoordinateComparisonOfMoving());
}

bool ManMoveDetectionD(void)
{
	return (Man.x > 0 && CoordinateComparisonOfMoving());
}

/*�ж����������ƶ�*/
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

/*����ש������*/
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
	printf("�������������Ĵ�����");
	scanf_s("%s", &tmp.name);
	tmp.score = Score;
	fp = fopen("rank.txt", "a");
	if (fp == NULL)
	{
		printf("cannot open the files\n");
		system("pause");
		return -1;//����ļ����ִ��󷵻�-1  
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
	for (i = 0; i < n - 1; i++)//����ð�ݷ��������� 
	{
		k = i;
		for (j = i + 1; j < n; j++)
			if (tmp[j].score > tmp[k].score)//����Ƚϴ�С  
				k = j;
		temp = tmp[k];
		tmp[k] = tmp[i];
		tmp[i] = temp;//����������ʱ�������ݽ���
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
	printf("\n\n������Ϸ��(Y������,����������˳�):");
	scanf_s("%c", &ch);
	return (ch == 'Y' || ch == 'y');
}
