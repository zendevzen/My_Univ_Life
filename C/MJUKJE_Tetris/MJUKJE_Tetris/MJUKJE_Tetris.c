
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//turboc.h���� �����
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
void clrscr();
void gotoxy(int x, int y);
int wherex();
int wherey();
void setcursortype(CURSOR_TYPE c);
#define delay(n) Sleep(n)							

//������� �ͺ������� ��������� ���̺귯���� �ֱ� ���ŷο��� �ʿ��� �Լ��� �ͺ���������� ���� �Խ��ϴ�.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//���� ����
#define Board_Height 20 //��������Ǵ� ������ ĭ�� ����
#define Board_Width 10// ĭ�� �ʺ�
#define BX 10 //������ ������ǥ
#define BY 5 //������ ������ǥ
//Ű���� ����
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define SPACE 32
#define ESC 27
#define ENTER 13
#define Z 90
#define z 122

#define WIN 99 //�ƹ����̳�
#define PAUSE 88

//������
#define COL GetStdHandle(STD_OUTPUT_HANDLE) //�̸� ������ �д�
#define Black SetConsoleTextAttribute(COL, 0x0000); //������
#define Yellow SetConsoleTextAttribute(COL, 0x000e); //�����
#define Blue SetConsoleTextAttribute(COL, 0x0009); //�Ķ���
#define High_Green SetConsoleTextAttribute(COL, 0x000a);//���λ�
#define SkyBlue SetConsoleTextAttribute(COL, 0x000b);//�ϴû�
#define Red SetConsoleTextAttribute(COL, 0x000c);//������
#define Plum SetConsoleTextAttribute(COL, 0x000d);//���ֻ�
#define Gold SetConsoleTextAttribute(COL, 0x0006);//�ݻ�
#define Gray SetConsoleTextAttribute(COL, 0x0008);//ȸ��
#define Original SetConsoleTextAttribute(COL, 0x0007);//������
#define High SetConsoleTextAttribute(COL,0x000d);//����

//���� ����
#define DO 260 //��Ÿ�갡 460�� ����
#define RE 320
#define MI 400
#define PA 450    
#define SOL 540
#define RA 630
#define SI 720




//�������� ����
int board[Board_Width + 2][Board_Height + 2];//2���� �迭�� ������ ����
int block_x;//������ġ x
int block_y;//������ġ y
int preview_x;//�̸����� ��ǥ
int preview_y;
int block;//���� ����
int spin;//���� ���ɻ���
int next_block;//���� ��������
int clear_Score;//�ܰ躰 Ŭ���� ����
int game_Speed;//������ �ӵ� �� ���ӳ��̵��� ���� �ӵ�
int game_Level = 1;//���� ���� 1�� �ʱ�ȭ
int score = 0;//���� ���� 0���� �ʱ�ȭ
int save_block = 7;//������� ó���� ����� �ϱ⿡ 0~6�� ��� ������ ����

				   //����� �� ������ ����
enum { PREVIEW, EMPTY, BRICK, WALL };			//������� 0 1 2 3�� �ν���
char *tile_style[] = { "��", " ","��","��" }; //0 1 2 3�� ���� ��Ÿ���°� 


										   //��ǥ ����ü
typedef struct Point//���� ����ü�� ��Ÿ��
{
	int x, y;
}Point;

//���� ��� �� ���������� ���� ǥ���� ��ǥ�� ��������
Point shape[7][4][4] = //[���� ����][ȸ������][�׿����� ��ǥ] �� 7 4 4 �� ����ü ����Ʈ�� 3���� �迭 
{
	{ { -1,0,0,0,1,0,2,0 },{ 0,2,0,1,0,0,0,-1 },{ -1,0,0,0,1,0,2,0 },{ 0,2,0,1,0,0,0,-1 } },						//�����̺���
{ { 0,0,-1,0,0,-1,-1,-1 },{ 0,0,-1,0,0,-1,-1,-1 },{ 0,0,-1,0,0,-1,-1,-1 },{ 0,0,-1,0,0,-1,-1,-1 } },			//�׸𳭺���
{ { 0,0,-1,0,0,-1,1,-1 },{ 0,0,0,1,-1,0,-1,-1 },{ 0,0,-1,0,0,-1,1,-1 },{ 0,0,0,1,-1,0,-1,-1 } },				//���κ��� 2���
{ { 0,0,-1,-1,0,-1,1,0 },{ 0,0,-1,0,-1,1,0,-1 },{ 0,0,-1,-1,0,-1,1,0 },{ 0,0,-1,0,-1,1,0,-1 } },				//���κ��� s���
{ { 0,0,-1,0,1,0,-1,-1 },{ 0,0,0,-1,0,1,1,-1 },{ 0,0,-1,0,1,0,1,1 },{ 0,0,0,-1,0,1,-1,1 } },					//������ ������
{ { 0,0,1,0,-1,0,1,-1 },{ 0,0,0,-1,0,1,1,1 },{ 0,0,1,0,-1,0,-1,1 },{ 0,0,0,1,0,-1,-1,-1 } },					//������
{ { 0,0,-1,0,1,0,0,-1 },{ 0,0,0,-1,0,1,1,0 },{ 0,0,-1,0,1,0,0,1 },{ 0,0,-1,0,0,-1,0,1 } }						//�Ǻ���
};

//�Լ� ���� ����
void PrintMainScreen();					//���� ��ũ�� ��� �Լ�
void Clean_Board();						//���� ����û��
void Game_LevelSet(int select_Level);	//���� ���̵�����
void PrintGameScreen();					//����ȭ�� ǥ��
void Print_NextBlock(BOOL show);		//���� ���� ǥ��
void Print_Block(BOOL show);			//������� ǥ��
void GameClear();						//���� Ŭ���� �Լ�
void GameOver();						//���� ���� �Լ�
int Play_Game();						//���� �÷��� �����Լ�
int InputKey();							//Ű���� �Է�Ű �����Լ�
void TestFull();						//������ �����ִ� �Լ�
BOOL MoveDown();						//Ű �ٿ�� �����Ǵ� �Լ� �������� �ִ���
void DrawBoard();						//���� �׷��ִ� �Լ�
int GetAround(int r, int x, int y);		//�ֺ��� ���Ǵµ� ����
void BlockColor(int block);				//���� ������ ����
int SelectMenu();						//�޴�����
void BlockSave();//���� ���̺��
void Print_SaveBlock(BOOL show);		//���̺�� ������ ����ϴ� �Լ�
void Clean_Save();						//���� ������ �Ҷ� ���̺� ������ û�����ش�
int SelectLevel();						//������ �����ϴ� �Լ�




void main()
{

	while (1)							//Ż���Ҷ� ���� �ݺ�
	{
		Clean_Board();					//���� ���� û���ѹ�
		game_Level = 1;					//���� �ʱ�ȭ
		Game_LevelSet(game_Level);		//�Լ��� �־� ������ �´� Ŭ���� ������ �ӵ����� �ʱ�ȭ ���ش�
		score = 0;						//�ٽý����ҋ��� ����� ���� �ʱ�ȭ
		save_block = 7;

		clrscr();						//��ü ȭ�� �����
		setcursortype(NOCURSOR);		//Ŀ�� �����
		PrintMainScreen();				//���� ȭ�� ���
		clrscr();						//��ü ȭ�� �����
		PrintGameScreen();				//���� ȭ�� ���
		if (Play_Game() == WIN)			//���� �ܰ� Ŭ��� �Ǹ�
		{
			while (1)
			{
				game_Level = (game_Level == 5) ? game_Level : game_Level + 1;	//3�� �����ڿ� ���� ���� 5�� �ƴϸ� +1���� 5�����̸� ��� ����
				Game_LevelSet(game_Level);										//�װ��� �Լ��� �־� ������ ó��

				clrscr();														//��ü ȭ�� ����
				PrintGameScreen();												//�ٽ� ����ȭ�� ���
				if (Play_Game() != WIN) break;									// �ܰ� Ŭ����� ���Ϲ� Ż��
			}
		}

	}
}


void Game_LevelSet(int select_Level)	//������ �Է¹����� �׿��´� ���̵��� �������ִ� �Լ�
{
	switch (select_Level)				//���� ����
	{
	case 1:
		clear_Score = 10000;				//�ܰ躰 Ŭ��������
		game_Speed = 22;				//������ �������� ���ǵ� ���ڰ� Ŭ���� ����
		break;
	case 2:
		clear_Score = 20000;
		game_Speed = 15;
		break;
	case 3:
		clear_Score = 40000;
		game_Speed = 10;
		break;
	case 4:
		clear_Score = 80000;
		game_Speed = 6;
		break;
	case 5:
		clear_Score = 300000;
		game_Speed = 3;
		break;
	}
}

void BlockColor(int block)																			//���Ϻ��� �� �����صδ°�
{
	if (block == 0) Red;
	if (block == 1) High_Green;
	if (block == 2) Gold;
	if (block == 3) Plum;
	if (block == 4) Blue;
	if (block == 5) SkyBlue;
	if (block == 6) Yellow;
	if (block == 9) Original;
}


void PrintMainScreen()
{
	system("mode con cols=80 lines=30");//�ý��� �󿡼� x��ǥ 0~79���� y��ǥ 0~29���� âũ�⸦ ����
	int select_Level = 1;					//����� �޴� ��ȣ

											//��Ʈ���� ���� ���
	gotoxy(8 + 10, 6);   Yellow puts("����");		//puts�� ���� ������ \n�� �׶��׶� ���� �����Ƽ��̴�
	gotoxy(8 + 12, 7);     Yellow puts("��");
	gotoxy(8 + 12, 8);     Yellow puts("��");
	gotoxy(8 + 12, 9);     Yellow puts("��");
	gotoxy(8 + 12, 10);    Yellow puts("��");

	gotoxy(8 + 17, 6);   High_Green puts("����");
	gotoxy(8 + 17, 7);   High_Green puts("��");
	gotoxy(8 + 17, 8);   High_Green puts("����");
	gotoxy(8 + 17, 9);   High_Green puts("��");
	gotoxy(8 + 17, 10);  High_Green puts("����");

	gotoxy(8 + 24, 6);   SkyBlue puts("����");
	gotoxy(8 + 26, 7);     SkyBlue puts("��");
	gotoxy(8 + 26, 8);     SkyBlue puts("��");
	gotoxy(8 + 26, 9);     SkyBlue puts("��");
	gotoxy(8 + 26, 10);    SkyBlue puts("��");

	gotoxy(8 + 31, 6);   Red puts("���");
	gotoxy(8 + 31, 7);   Red puts("��  ��");
	gotoxy(8 + 31, 8);   Red puts("����");
	gotoxy(8 + 31, 9);   Red puts("�� ��");
	gotoxy(8 + 31, 10);  Red puts("��  ��");

	gotoxy(8 + 38, 6);   Yellow puts("����");
	gotoxy(8 + 40, 7);     Yellow puts("��");
	gotoxy(8 + 40, 8);     Yellow puts("��");
	gotoxy(8 + 40, 9);     Yellow puts("��");
	gotoxy(8 + 38, 10);  Yellow puts("����");

	gotoxy(8 + 45, 6);   High_Green puts("����");
	gotoxy(8 + 45, 7);   High_Green puts("��");
	gotoxy(8 + 45, 8);   High_Green puts("����");
	gotoxy(8 + 49, 9);   High_Green puts("��");
	gotoxy(8 + 45, 10);  High_Green puts("����");
	//���� ���
	gotoxy(8 + 14, 13);  Original puts("��������������α׷� ��â�� ������");
	gotoxy(8 + 14, 14);  SkyBlue puts("    5 ��   �� �� ��   �� �� ��");
	//�޴� 3����
	gotoxy(16, 18);  Gray puts("�� ��   START GAME !");
	gotoxy(19, 20);  Gray puts("��   SET START LEVEL !");
	gotoxy(19, 22);  Gray puts("��   EXIT GAME !");
	Original;											//������ ���� ������� �����ִ� �κ�



	while (1)												//����ε� �޴��� ������ ���� �ݺ�
	{
		select_Level = SelectMenu();						//���÷����� ������ ����
		break;
	}
	if (select_Level == 1) Game_LevelSet(select_Level);		//1�� �޴� ������ ���ý� ��������
	else if (select_Level == 2)								//2�� �޴� �������� ���ý�
	{
		while (1)											//����ε� ���� �������� �ݺ�
		{
			clrscr();										//��ü ȭ�� û��
			gotoxy(8 + 11, 5);  Yellow puts("��");
			gotoxy(8 + 11, 6);  Yellow puts("��");
			gotoxy(8 + 11, 7);  Yellow puts("��");
			gotoxy(8 + 11, 8);  Yellow puts("��");
			gotoxy(8 + 11, 9);  Yellow puts("����");

			gotoxy(8 + 19, 5);  Yellow puts("����");
			gotoxy(8 + 19, 6);  Yellow puts("��");
			gotoxy(8 + 19, 7);  Yellow puts("����");
			gotoxy(8 + 19, 8);  Yellow puts("��");
			gotoxy(8 + 19, 9);  Yellow puts("����");

			gotoxy(8 + 27, 5);  Yellow puts("��  ��");
			gotoxy(8 + 27, 6);  Yellow puts("��  ��");
			gotoxy(8 + 27, 7);  Yellow puts("��  ��");
			gotoxy(8 + 27, 8);  Yellow puts(" ���");
			gotoxy(8 + 27, 9);  Yellow puts("  ��");


			gotoxy(8 + 35, 5);  Yellow puts("����");
			gotoxy(8 + 35, 6);  Yellow puts("��");
			gotoxy(8 + 35, 7);  Yellow puts("����");
			gotoxy(8 + 35, 8);  Yellow puts("��");
			gotoxy(8 + 35, 9);  Yellow puts("����");

			gotoxy(8 + 43, 5);  Yellow puts("��");
			gotoxy(8 + 43, 6);  Yellow puts("��");
			gotoxy(8 + 43, 7);  Yellow puts("��");
			gotoxy(8 + 43, 8);  Yellow puts("��");
			gotoxy(8 + 43, 9);  Yellow puts("����");

			gotoxy(8 + 51, 5);  Yellow puts("��");
			gotoxy(8 + 51, 6);  Yellow puts("��");
			gotoxy(8 + 51, 7);  Yellow puts("��");
			gotoxy(8 + 51, 8);  Yellow puts("");
			gotoxy(8 + 51, 9);  Yellow puts("��");

			gotoxy(16, 15);  SkyBlue puts("�� PRACTICE MODE");			//�޴� 5�� ���
			gotoxy(19, 17);  High_Green puts("EASY MODE");
			gotoxy(19, 19);  Yellow puts("NORMAL MODE");
			gotoxy(19, 21);  Plum puts("HARD MODE");
			gotoxy(19, 23);  Red puts("HELL MODE");

			select_Level = SelectLevel();							//����� ������ ������ ����
			game_Level = select_Level;								//������ ���� ������ ����

			Game_LevelSet(select_Level);							//�����Լ��� �ְ� �����ϱ�
			if (select_Level > 0 && select_Level < 6) break;		//�������� ������ ������ ���Ϲ� Ż��
		}
	}
	else {
		clrscr();
		gotoxy(8 + 15, 11);   Yellow puts("���");
		gotoxy(8 + 15, 12);  Yellow puts("��  ��");
		gotoxy(8 + 15, 13);  Yellow puts("����");
		gotoxy(8 + 15, 14);  Yellow puts("��  ��");
		gotoxy(8 + 15, 15);  Yellow puts("����");

		gotoxy(8 + 25, 11);   Yellow puts("��  ��");
		gotoxy(8 + 25, 12);  Yellow puts("��  ��");
		gotoxy(8 + 25, 13);  Yellow puts(" ���");
		gotoxy(8 + 25, 14);  Yellow puts("  ��");
		gotoxy(8 + 25, 15);  Yellow puts("  ��");

		gotoxy(8 + 35, 11);  Yellow puts("����");
		gotoxy(8 + 35, 12);  Yellow puts("��");
		gotoxy(8 + 35, 13);  Yellow puts("����");
		gotoxy(8 + 35, 14);  Yellow puts("��");
		gotoxy(8 + 35, 15);  Yellow puts("����");

		gotoxy(8 + 45, 11); Red puts("");
		gotoxy(8 + 45, 12); Red puts("  ��    ��");
		gotoxy(8 + 45, 13); Red puts("");
		gotoxy(8 + 45, 14); Red puts("��        ��");
		gotoxy(8 + 45, 15); Red puts("  �����");
		Black														//�ƹ�Ű�� ������¸� ���ֱ��
			exit(0);

	}//3�� ������ ������ ���� ����
	Original
}

void Clean_Board()													//���� ���� û�� �� ���屸����� �迭�� ���� �ʱ�ȭ
{
	int x, y;
	for (x = 0; x < Board_Width + 2; x++)							//���Ӻ���κ��� x��ǥ �ϳ��� ��� y��ǥ�� �����ϱ� ���� for���� ���
	{
		for (y = 0; y < Board_Height + 2; y++)						//�ʺ�� ���̸� �����ʰ� ��Ʈ��
		{
			board[x][y] = (x == 0 || y == 0 || x == Board_Width + 1 || y == Board_Height + 1 ? WALL : EMPTY); //���κ��� ���� ��� �ƴѰ��� ������� �д�
		}
	}
}


void PrintGameScreen()												//���� ȭ�� ���
{
	system("mode con cols=80 lines=30");//�ý��� �󿡼� x��ǥ 0~79���� y��ǥ 0~29���� âũ�⸦ ����
	int x, y;
	for (x = 0; x < Board_Width + 2; x++)
	{
		for (y = 0; y < Board_Height + 2; y++)
		{
			gotoxy(x * 2 + BX, y + BY);								//�ش� ��ǥ�� �̵��ؼ�
			puts(tile_style[board[x][y]]);							//���� ������ ��Ȳ�� ���� ���������� ������ش�
		}
	}

	//ȭ�� ����
	gotoxy((BX * 2) + 16, 5);  Blue puts("  �����������  ���α׷�  ");								//puts���� �̸� �����ص� ������ �ǹ���
	gotoxy((BX * 2) + 16, 6);  SkyBlue puts("     ��â��   ������      ");
	gotoxy((BX * 2) + 16, 7);  Original printf("   %d �ܰ�   �� ���� : %d\n", game_Level, score);	//puts�δ� ���� ����� ����Ƿ� printf�� ����Ѵ�
	gotoxy((BX * 2) + 16, 8);  Original puts("�ââââââââââââ�");
	gotoxy((BX * 2) + 16, 9);  Original puts("��          ��          ��");
	gotoxy((BX * 2) + 16, 10); Original puts("��          ��          ��");
	gotoxy((BX * 2) + 16, 11); Original puts("��          ��          ��");
	gotoxy((BX * 2) + 16, 12); Original puts("��          ��          ��");
	gotoxy((BX * 2) + 16, 13); Original puts("�ââââââââââââ�");
	gotoxy((BX * 2) + 16, 15); Red puts("            5 ��          ");
	gotoxy((BX * 2) + 16, 16); SkyBlue puts("    �� �� ��   �� �� ��   ");
	gotoxy((BX * 2) + 16, 18); Original puts("�âââ� ���ӹ�� �âââ�");
	gotoxy((BX * 2) + 16, 19); Original puts("��  ��   : ���� ȸ��    ��");
	gotoxy((BX * 2) + 16, 20); Original puts("�� ���  : �¿� �̵�    ��");
	gotoxy((BX * 2) + 16, 21); Original puts("��  ��   : ���� ������  ��");
	gotoxy((BX * 2) + 16, 22); Original puts("�� space : ��� ������  ��");
	gotoxy((BX * 2) + 16, 23); Original puts("��   Z   : ���� ����    ��");
	gotoxy((BX * 2) + 16, 24); Original puts("�� PAUSE : �Ͻ� ����    ��");
	gotoxy((BX * 2) + 16, 25); Original puts("�� E S C : �� �� ��     ��");
	gotoxy((BX * 2) + 16, 26); Original puts("�ââââââââââââ�");
}


void DrawBoard()													//���带 �׸���
{
	int x, y;
	for (x = 1; x < Board_Width + 1; x++)
	{
		for (y = 1; y < Board_Height + 1; y++)
		{
			gotoxy(BX + x * 2, BY + y);
			Original puts(tile_style[board[x][y]]);					//���� �������� ���带 ����Ѵ�
		}
	}
	gotoxy((BX * 2) + 16, 7);  Original printf("   %d �ܰ�   �� ���� : %d\n", game_Level, score);	//���� �������� ������ ������ ����Ѵ�
}

BOOL MoveDown()														//�Ʒ��� �������� �� ������ִ� �Լ�
{
	int i;

	if (GetAround(spin, block_x, block_y + 1) == EMPTY || PREVIEW)	//������ǥ�� �Ʒ��� ����ְų� �̸����� ������ ��쿡
	{
		Print_Block(FALSE);											//������ ��� �����
		block_y++;													//��ĭ������
		BlockColor(block); Print_Block(TRUE);											//������ ����Ѵ�
		return TRUE;												//Ʈ�簪�� �������ش�
	}
	else
	{
		for (i = 0; i < 4; i++)
		{
			board[block_x + shape[block][spin][i].x][block_y + shape[block][spin][i].y] = BRICK;	//���ڸ��� ������ ����Ѵ�
		}
		Print_NextBlock(FALSE);																	//���� ������ �Ⱥ��̰� �Ѵ�
		TestFull();																				//������ ��á���� Ȯ��
		Beep(DO, 20);																			//ȿ����
		return FALSE;
	}
}


int GetAround(int r, int x, int y)																	//���а� �ű� �� ��ĭ�̵��� ������ ��ġ�� ���� �ִ��� �Ǵ���
{
	int i, k = EMPTY;																				//k�� �����, enum���� ���� �����δ� 1�� �ʱ�ȭ�ص�
	for (i = 0; i < 4; i++)
	{
		k = max(k, board[shape[block][r][i].x + x][shape[block][r][i].y + y]);						//�ƽ��� ���� ū�� ��ȯ �� �����䳪 ������� �ƴϸ� K���� �ٲ�� �̸������ 0�ǰ� ������� 1�̶� �̸������ �ν��� ����
																									//enum���� �̸������ ��ĭ�� 0�� 1 ���ϰ� ���� 2�� 3���� ���� �����ޱ⿡ ������ k�ǰ� �� 1�� ���Ϸ��� �ֺ��� ���̳� ������ �־�� �Ѵ� 
		if (k != EMPTY || PREVIEW) break;															//��ų� �̸����Ⱑ �ƴϸ� Ż��
	}
	return k;				//k�� ���� ������ �ش� ���Լ��� �ֺ��� ���̳� ������ �ִ��� �Ǵ��ϴµ� ���δ� if(GetAround(r,x,y)==EMPTY || PREVIEW)�̷��� ���� 
							//k���� 0�̰ų� 1�϶��� �������� �ߵ� �� ���̰ų� ������ �ֺ��� ������ �������� �ߵ����� �ʴ� ���̴�
}



void TestFull()																						//���� �������ִ��� �Ǻ�
{
	int x, y;
	int a;																							//y�� �ӽ������� ����

	for (y = 1; y < Board_Height + 1; y++)
	{
		for (x = 1; x < Board_Width + 1; x++)
		{
			if (board[x][y] != BRICK) break;														//������ ��� ������ �ƴϸ� �� ����� ������ Ż��
		}
		if (x == Board_Width + 1)																	//������ ������ ��� �����϶� �� �� ������ ������ ���� ����� �Ѿ��		
		{
			for (a = y; a > 1; a--)																	//a�� y���� �����ϰ� 1�� �ɋ� ����
			{																						//�� ������ ������ ���
				for (x = 1; x < Board_Width + 1; x++)
				{
					board[x][a] = board[x][a - 1];													//�Ʒ��ٿ� ��ĭ���� �ٿ�Ҹ� �׸��� �� ��ĭ�� ������
				}
			}

			score += 1000;																			//���ϳ��� ���� 1000�� ��
			DrawBoard();																			//�ٽü����� ���带 �׸�
			Beep(DO + 262, 20);																		//ȿ����
			Beep(MI + 262, 20);
			Beep(RE + 262 + 460, 30);
			delay(50);
		}
	}
}

int InputKey()																						//Ű�� �����°͵��� �� ó�����ִ� �Լ�
{
	int ch;																							//����Ű�� ������ ���� �ƽ�Ű�ڵ尪���� ����ȴ�
	int temp_Spin;																					//�ӽ�  ���ɰ��� �����ϴ� ����

	if (_kbhit())																					//Ű���尡 ���� ������ �Ǵ���
	{																								//������ 1 �ƴϸ� 0�� ��ȯ��
		ch = _getch();																				//����Ű�� �ٷ� ch ������ �����Ѵ�
																									//����Ű�� Ű���� �Է�
		if (ch == 0xE0 || ch == 0)																	//����Ű�� �ƴ� Ȯ��Ű�� �ԷµǾ��� ��쿡!
		{
			ch = _getch();																			//����Ű�� ������ ����
			switch (ch)
			{
			case UP:																			//�� ����Ű �� ���
			{
				temp_Spin = (spin == 3) ? 0 : spin + 1;											//ȸ������ 4���� �� 3�̸� 0���� ���ư���
				if (GetAround(temp_Spin, block_x, block_y) == EMPTY || PREVIEW)					//ȸ���� �ɸ����Ÿ��°� Ȯ��
				{
					Print_Block(FALSE);															//��� �����
					spin = temp_Spin;															//�ӽ� ȸ������ ��¥ ȸ������ ����
					BlockColor(block); Print_Block(TRUE);															//����ع����� ��
				}
				break;
			}
			case RIGHT:																			//������ ����Ű
			{
				if (GetAround(spin, block_x + 1, block_y) == EMPTY || PREVIEW)					//�������� ��ĭ�̰ų� �̸����� �ϰ��
				{
					Print_Block(FALSE);															//��� �����
					block_x++;																	//���������� �̵�
					BlockColor(block); Print_Block(TRUE);															//����� �ش�
				}
				break;
			}
			case DOWN:																			//�Ʒ��� ����Ű
			{
				if (MoveDown() != TRUE)															//����ٿ� �Լ��� ���� ��ȯ���� ������ �� ��򰡿� �������
				{
					return TRUE;																//���� ��ȯ
				}
				break;
			}
			case LEFT:																			//���� ����Ű
			{
				if (GetAround(spin, block_x - 1, block_y) == EMPTY || PREVIEW)					//������ ��ĭ�̰ų� �̸����� �ϰ��
				{
					Print_Block(FALSE);															//�����
					block_x--;																	//���� ��ĭ�̵�
					BlockColor(block); Print_Block(TRUE);															//���
				}
				break;
			}
			}

		}
		else if (ch == ' ')																			//SPACE�� �Է½�
		{
			while (MoveDown())																		//����ٿ��� ���� �ݺ�
			{
			}
			return TRUE;																			//���� ��ȯ
		}
		else if (ch == 'p' || ch == 'P')															//p�� P�� �Է� �Ǿ�����
		{
			clrscr();																				//ȭ�� û��
			gotoxy(15, 10);																			//�Ͻ����� ���� ����� ��ǥ�� �̵�
			Gray puts("��� ����...�ٽ� �����Ϸ��� �ƹ�Ű�� ��������.");							//���� ���
			_getch();																				//�Ű�� �ԷµǸ�
			clrscr();																				//ȭ�� û��
			PrintGameScreen();																		//����ȭ�� ���
			DrawBoard();																			//���� �׸���
			BlockColor(block); Print_Block(TRUE);													//���� ���
		}
		else if (ch == ESC)																			//�̿������Է½�
		{
			return ESC;																				//�̿����ø� ��ȯ
		}
		else if (ch == z)																			//z�� �Է½�
		{
			BlockSave();											//���̺�� �Լ�
		}
		else {}																						//������ ����
	}
	return FALSE;																					//������ ��ȯ
}

int Play_Game()																						//���� ��Ʈ�� �Լ� ���� �����
{

	int	nFrame = game_Speed;																		//�����Ӱ��� ���Ӽӵ��� �ʱ�ȭ
	int nStay;																						//���⿡ �����Ӱ��� �ְ� �ϳ��� �ٿ����°�
	int	StopCmd = 0;																				//WIN�̳� ESC���� ��� ����//���� ���� ����

	srand((unsigned)time(0));																		//�����κ�

	block = rand() % 7;																				//ó������ ���� ������ ���ϱ�

	while (1)
	{
		block_x = Board_Width / 2;																	//����� ������ �ϴ� ��
		block_y = 3;

		next_block = rand() % 7;																	//���� ���� ������ ���ϱ�
		spin = 0;																					//���������� ȸ������
		nStay = nFrame;																				//��ٸ� �ð��� ����


		BlockColor(block); Print_Block(TRUE);														//ù���� ���� ���������� �´� ����
		BlockColor(next_block); Print_NextBlock(TRUE);												//���� ���� ǥ��
		BlockColor(save_block); Print_SaveBlock(TRUE);												//���� ���� ǥ��

		if (GetAround(spin, block_x, block_y) != EMPTY || PREVIEW) break;							//��������θ� �����ϼ� �ְ� ���� �� ���������� Ż��

		while (1)
		{
			if (--nStay == 0)																		//��ٸ��� �ð��� �ٵǸ�
			{
				nStay = nFrame;																		//�ٽ��ѹ� ��ٸ��� �ð� �ʱ�ȭ
				if (MoveDown() == FALSE) break;														//������ �ٴڿ� ������ ���Ϲ� Ż��
			}

			StopCmd = (score >= clear_Score) ? WIN : InputKey();									//���� ������ Ŭ���� �����̴��̸� �ٽ� Ű�Է� �޴´�
			if (StopCmd != FALSE) break;															//���� ��žĿ�ǵ忡 ���� ������ Ż��

			delay(50);
		}
		if (StopCmd == ESC || StopCmd == WIN) break;												//�̱�ų� ESC�� Ż��

		block = next_block;																			//�����ִ� ���������� ������Ͽ� ����
	}

	if (StopCmd == WIN)																				//Ŭ����� Ŭ���� �Լ� �ҷ���
	{
		GameClear();
		return WIN;																					//�¸��� ��ȯ
	}

	else if (StopCmd == ESC)																		//esc�� ������ ��žĿ�ǵ尡 esc�ϋ�
		return ESC;																					//esc�� ��ȯ

	GameOver();																						//��� �ƴϾ ��Ż�� ������ ���ӿ���
	Original																						//�ƹ� ���� �ƴѰɷ� �ʱ�ȭ
		return 0;
}

void GameClear()																					//Ŭ���� �Լ�
{
	int x = 0, y = 12, count;
	clrscr();
	delay(300);
	for (count = 0; count <= 4; ++count)
	{
		gotoxy(x, y);
		Yellow puts("		  ���� ��       �����   ���   ����");							//Ŭ���� ���� ���
		Yellow puts("		��       ��       ��       ��    �� ��    ��");
		Yellow puts("		��       ��       ����� ����� �����");
		Yellow puts("		��       ��       ��       ��    �� ��  ��");
		Yellow puts("		  ���� ����� ����� ��    �� ��    ��");
		gotoxy(x, y);

		Beep(DO + 262 + 420, 40);																	//���� ���
		Beep(SOL + 262 + 420, 40);


		clrscr();																					//�׸��� ������� 0.1�ʸ��� �ݺ�
		delay(100);
	}
	clrscr();																						//ȭ�� �����
	Original																						//���� �ʱ�ȭ
}

void GameOver()																						//���� ���� �Լ�
{
	int x = 0, y = 12, count;
	clrscr();																						//ȭ�� û��
	for (count = 0; count <= 4; ++count)
	{
		gotoxy(x, y);
		Red puts("   ����   ���   ��      �� �����   ����   ��      �� ����� ����");	//���� ���
		Red puts(" ��       ��    �� ���  ��� ��       ��      �� ��      �� ��       ��    ��");
		Red puts(" ��  ��� ����� ��  ��  �� ����� ��      ��  ��    ��  ����� �����");
		Red puts(" ��    �� ��    �� ��      �� ��       ��      ��   ��  ��   ��       ��   ��");
		Red puts("   ���� ��    �� ��      �� �����   ����       ��     ����� ��    ��");
		gotoxy(x, y);

		Beep(SI + 262 + 420, 40);
		Beep(SOL + 262 + 420, 40);
		clrscr();																					//�׸��� ������� 0.2�ʸ��� �ݺ�
		delay(200);
	}
	clrscr();																						//ȭ�� �����
	PrintMainScreen();																				//�޴�ȭ�� ���
}

void Print_Block(BOOL show)																			//�츮�� �����̴� ���� ����Լ�
{
	int i, temp = 0;
	//�̸����⸦ ���� �κ�
	while (GetAround(spin, block_x, block_y + temp + 1) == EMPTY || PREVIEW)						//�ֺ��� ����ְų� �̸����� �϶���
	{
		temp++;																						//y�� �������� temp�� 1�� ���Ѵ� �� �Ʒ��� ��ĭ��
	}																								//�̸����� ����� ���� ��� �̸����⸦ �������� ���ϴ°�
	for (i = 0; i < 4; i++)																			//������ ��� 4���� ��ǥ�� ���� �� 4���� ���
	{
		gotoxy(BX + (shape[block][spin][i].x + block_x) * 2, BY + shape[block][spin][i].y + block_y + temp);//�̸����� ���� ��ǥ�� �̵���
		puts(tile_style[show ? PREVIEW : EMPTY]);													//�ҿ��� TRUE�� �ԷµǸ� �̸����� ���̰� FALSE�̸� ��������� �д�
	}
	//�̸����� �κг�
	//�̸������ �׳� ������¿��� �������� y��ǥ�� temp���� �����ֳ� �ȴ����ֳ��� ����
	for (i = 0; i < 4; i++)																			//������ ��� 4���� ��ǥ�� ���� �� 4���� ���
	{
		gotoxy(BX + (shape[block][spin][i].x + block_x) * 2, BY + shape[block][spin][i].y + block_y);// �̰� �׳� ������ ��ġ
		puts(tile_style[show ? BRICK : EMPTY]);														//�ҿ��� ���� ��µǸ� �׸��� �����̸� ��������� �д�
	}
}

void Print_NextBlock(BOOL show)
{
	int i;
	for (i = 0; i < 4; i++)																			//������ ��� 4���� ��ǥ�� ���� �� 4���� ���
	{
		gotoxy(BX + (shape[next_block][0][i].x + 16) * 2, BY + shape[next_block][0][i].y + 6);		//���� ������ �����ִ� ��ġ���� ȸ���� �⺻��
		puts(tile_style[show ? BRICK : EMPTY]);														//�ҿ��� ���� ��µǸ� �׸��� �����̸� ��������� �д�
	}
}

void Print_SaveBlock(BOOL show)																		//����� ������ ������
{
	int i;
	for (i = 0; i < 4; i++)																			//������ ��� 4���� ��ǥ�� ���� �� 4���� ���
	{
		gotoxy(BX + (shape[save_block][0][i].x + 22) * 2, BY + shape[save_block][0][i].y + 6);		//���� ������ �����ִ� ��ġ���� ȸ���� �⺻��
		puts(tile_style[show ? BRICK : EMPTY]);														//�ҿ��� ���� ��µǸ� �׸��� �����̸� ��������� �д�
	}
}

void BlockSave()										//���� ���� �Լ�
{																									//������ ������ �Ἥ �Լ� �ۿ����� ���ϵ��� �Ѵ�
	int temp;																						//������ ��ȭ�ɰ� �ӽ�����
	Print_Block(FALSE);																				//���ϰ� ��������� �����
	Print_SaveBlock(FALSE);
	if (save_block == 7) save_block = next_block;												//���ϰ��� 0~6�̴� ���尪�� 7�̸� ����Ȱ� ������ ���������� ��������¶�
	temp = block;																					//������ ������� ����
	block = save_block;																			//���̺� ������ ������Ͽ� ����
	save_block = temp;																			//���̺� ���Ͽ� ���� ���ϰ��� ����ִ� ������ ����
	if (block == 0 && block_x>8) block_x -= 1;													//������ �����϶� ��ǥ�� �� ����������� ������ ���� ������� ����ﶧ�� �������� ��ĭ �Ű����鼭 �ٲ�� �ٲ㼭 ��ħ
	BlockColor(save_block); Print_SaveBlock(TRUE);													//������ϰ� �׳ɺ����� ���
	BlockColor(block); Print_Block(TRUE);															//���� �����÷��� ���� ����
}





void Clean_Save()																					//������� ��°��� û��
{
	int x, y;
	for (x = 20; x < 49; x++)
	{
		for (y = 5; y < 9; y++)
		{
			board[x][y] = (EMPTY);																	//��ĭ���� ǥ��
		}
	}
}


int SelectMenu()																					//�޴� ����ȭ��ǥ �����̴� �Լ�
{
	int ch = _getch();																				//����Ű�� ch�� ����
	int MenuNum = 1;

	while (ch != ENTER)																				//���Ͱ� ������ ������
	{
		if (_kbhit())																				//Ű���尡 ���� ������ �Ǵ���
		{
			ch = _getch();																			//�ٷ� �����ϴ� ���ɾ�

			while (1)
			{
				ch = _getch();																		//�ٽ��ѹ� ����
				Sleep(5);																			//���� ���� ������
				switch (ch)
				{

				case UP:
				{
					gotoxy(16, 16 + (2 * MenuNum));  High puts("��");								//�޴��� �´� ��ġ�� ȭ��ǥ�� ��ġ��Ŵ
					if (MenuNum == 1)																//1�ϰ�쿡 ���� ������ 3���� ������
					{
						gotoxy(16, 16 + (2 * MenuNum));   High puts("  ");							//ȭ��ǥ�� �����
						MenuNum = 3;																//�ű��
						gotoxy(16, 16 + (2 * MenuNum));  High puts("��");							//��ȭ��ǥ�� ���
					}
					else
					{
						gotoxy(16, 16 + (2 * MenuNum));   High puts("  ");
						MenuNum -= 1;
						gotoxy(16, 16 + (2 * MenuNum));  High puts("��");
					}
					Beep(861, 20);																	//ȿ����
					break;
				}


				case DOWN:
				{
					gotoxy(16, 16 + (2 * MenuNum));  High puts("��");
					if (MenuNum == 3)																//3�ϰ�쿣 �Ʒ������� 1�� ������
					{
						gotoxy(16, 16 + (2 * MenuNum));   High puts("  ");
						MenuNum = 1;
						gotoxy(16, 16 + (2 * MenuNum));   High puts("��");
					}
					else
					{
						gotoxy(16, 16 + (2 * MenuNum));   High puts("  ");
						MenuNum += 1;
						gotoxy(16, 16 + (2 * MenuNum));  High puts("��");
					}
					Beep(861, 20);
					break;
				}


				}
				if (ch == ENTER)																	//���Ͱ� ������
				{
					if (MenuNum != 3)																//3 �� �����Ⱑ �ƴҰ�쿡 ��ε����
					{
						Beep(461, 20);
						Beep(601, 20);
						Beep(801, 20);
						Beep(1061, 50);
					}
					else {}																			//�������� ����
					break;
				}
			}
		}
		break;
	}
	Original;
	return MenuNum;																					//���� ��ȣ�� ��ȯ
}



int SelectLevel()																					//���� ���� ������ �Լ� ȭ��ǥ ǥ��
{
	int ch = _getch();
	int game_Level = 1;

	while (ch != ENTER)
	{
		if (_kbhit())																				//Ű���尡 ���� ������ �Ǵ���
		{

			while (1)
			{
				ch = _getch();
				Sleep(5);
				switch (ch)
				{

				case UP:
				{
					gotoxy(16, 13 + 2 * (game_Level));   High; puts("��");
					if (game_Level == 1)
					{
						gotoxy(16, 13 + 2 * (game_Level));  High; puts("  ");
						game_Level = 5;
						gotoxy(16, 13 + 2 * (game_Level));   High; puts("��");
					}
					else
					{
						gotoxy(16, 13 + 2 * (game_Level));  High; puts("  ");
						game_Level -= 1;
						gotoxy(16, 13 + 2 * (game_Level));  High; puts("��");
					}
					Beep(861, 20);
					break;
				}


				case DOWN:
				{
					gotoxy(16, 13 + 2 * (game_Level));   High; puts("��");
					if (game_Level == 5)
					{
						gotoxy(16, 13 + 2 * (game_Level));   High; puts("  ");
						game_Level = 1;
						gotoxy(16, 13 + 2 * (game_Level));   High; puts("��");
					}
					else
					{
						gotoxy(16, 13 + 2 * (game_Level));   High; puts("  ");
						game_Level += 1;
						gotoxy(16, 13 + 2 * (game_Level));   High; puts("��");
					}
					Beep(861, 20);
					break;
				}


				}
				if (ch == ENTER)
				{
					Beep(461, 20);
					Beep(601, 20);
					Beep(801, 20);
					Beep(1061, 50);

					break;
				}
			}
		}
		break;
	}
	Original;
	return game_Level;
}

//�̹����δ� �ͺ��� ���� �Լ���
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ȭ���� ��� �����.
void clrscr()
{
	system("cls");
}

// Ŀ���� x,y��ǥ�� �̵���Ų��.
void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

// Ŀ���� x ��ǥ�� �����Ѵ�.
int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
	return BufInfo.dwCursorPosition.X;
}

// Ŀ���� y��ǥ�� �����Ѵ�.
int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
	return BufInfo.dwCursorPosition.Y;
}

// Ŀ���� ����ų� �ٽ� ǥ���Ѵ�.
void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////