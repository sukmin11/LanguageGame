#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define SIZE 1000
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

#define WIDTH 9
#define HEIGHT 25

int highscore = 0;
int health = 3;

void saveScore(int score) {
	FILE* file = fopen("highscore.txt", "w");
	if (file == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
		return;
	}
	fprintf(file, "%d\n", score);
	fclose(file);
}

int loadScore() {
	highscore;
	FILE* file = fopen("highscore.txt", "r");
	if (file == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
		return -1;
	}
	fscanf(file, "%d", &highscore);
	fclose(file);
	return highscore;
}

int score = 0;

typedef struct Character
{
	int x;
	int y;
	const char* shape;
}Character;

char map[HEIGHT][WIDTH] = {
	{'1','1','1','1','1','1','1','1','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','1'},
	{'1','1','1','1','1','1','1','1','1'},
};

void setColor(int textColor, int bgColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, textColor | (bgColor << 4));
}

void Render()
{
	highscore = loadScore();

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (map[i][j] == '0' || map[i][j] == '3')
				printf("  ");
			else if (map[i][j] == '1')
				printf("■");
			else if (map[i][j] == '2')
			{
				setColor(9, 0);
				printf("※");
				setColor(7, 0);
			}
			else if (map[i][j] == '4')
			{
				setColor(4, 0);
				printf("♥");
				setColor(7, 0);
			}
			else if (map[i][j] == '5')
			{
				setColor(6, 0);
				printf("★");
				setColor(7, 0);
			}
		}
		printf("\n");
	}
	printf("health:");
	for (int i = 0; i < health; i++)
	{
		setColor(4, 0);
		printf("♥");
		setColor(7, 0);
	}
	printf("\n");
	printf("score : %d\n", score);
	printf("highscore : %d\n", highscore);
}

void Position(int x, int y)
{
	// X와 Y축을 설정하는 구조체입니다.
	COORD position = { x, y };

	// 콘솔 커서의 좌표를 설정하는 함수입니다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void startscreen(int x, int y, int i, int j) {
	printf("■■■■■■■■■\n");
	printf("■              ■\n");
	printf("■ 피하기  게임 ■\n");
	printf("■              ■\n");
	printf("■              ■\n");
	printf("■■■■■■■■■\n");
	printf("\n");
	printf("\n");
	printf("   "); setColor(x, y); printf(" 게임 시작 "); setColor(7, 0);
	printf("\n\n\n");
	printf("   "); setColor(i, j); printf(" 게임 종료 "); setColor(7, 0);
}

int main()
{
	int again = 0;
	char key = 0;

	srand(time(NULL));

	system("mode con: cols=18 lines=30");

	startscreen(7, 0, 7, 0);

	while (1)
	{

		if (_kbhit())
		{
			key = _getch();

			if (key == -32)
			{
				key = _getch();
			}

			switch (key)
			{
			case UP: {
				system("cls");
				system("mode con: cols=18 lines=30");
				startscreen(0, 7, 7, 0);
				again = 1;
				break;
			}
			case DOWN: {
				system("cls");
				system("mode con: cols=18 lines=30");
				startscreen(7, 0, 0, 7);
				again = 2;
				break;
			}
			}

			if (again == 1 && GetAsyncKeyState(VK_SPACE) & 0x0001)
			{
				again = 0;
				break;
			}
			else if (again == 2 && GetAsyncKeyState(VK_SPACE) & 0x0001)
				goto EXIT;
		}
	}

	const char* select[3];

	select[0] = "Play Again?\nYES\nNO\n";
	select[1] = "Play Again?\nYES  ←\nNO\n";
	select[2] = "Play Again?\nYES\nNO   ←\n";

	Character character = { 8,22,"△" };

	int hole1 = 0;
	int hole2 = 0;
	int line1 = 1;
	int line2 = 1;
	int line3 = 1;
	int line4 = 1;
	int level = 150;
	int speed = 0;
	int itemSpeed = 200;
	int item = 0;
	int heart = 0;
	int heartOn = 0;
	int star = 0;
	int starOn = 0;
	int defense = 0;

AGAIN:

	hole1 = rand() % 7 + 1;

	for (int i = 1; i < 8; i++)
		map[line1][i] = '2';

	map[line1][hole1] = '3';
	system("mode con: cols=18 lines=30");
	Render();

	while (1)
	{
		long long CurrentTime = clock();

		for (int i = 1; i < HEIGHT - 1; i++)
		{
			for (int j = 1; j < WIDTH - 1; j++)
			{
				map[i][j] = '0';
			}
		}

		if (heartOn == 1)
		{
			map[line3][heart] = '4';
		}

		if (starOn == 1)
		{
			map[line4][star] = '5';
		}

		for (int i = 1; i < 8; i++)
		{
			map[line1][i] = '2';
			map[line1][hole1] = '3';
		}

		if (line1 != line2)
		{
			for (int i = 1; i < 8; i++)
			{
				map[line2][i] = '2';
				map[line2][hole2] = '3';
			}

		}

		if (line1 == 15)
		{
			line2 = 1;
			hole2 = rand() % 7 + 1;
			for (int i = 1; i < 8; i++)
			{
				map[line2][i] = '2';
			}

			map[line2][hole2] = '3';
		}

		if (line2 == 15)
		{
			line1 = 1;
			hole1 = rand() % 7 + 1;
			for (int i = 1; i < 8; i++)
			{
				map[line1][i] = '2';
			}

			map[line1][hole1] = '3';
		}

		for (int i = 1; i < WIDTH - 1; i++)
		{
			map[24][i] = '1';
		}

		if (_kbhit())
		{
			key = _getch();

			if (key == -32)
			{
				key = _getch();
			}

			switch (key)
			{
			case LEFT:
				if (map[character.y][character.x / 2 - 1] != '1')
				{
					character.x -= 2;
				}
				break;
			case RIGHT:
				if (map[character.y][character.x / 2 + 1] != '1')
				{
					character.x += 2;
				}
				break;
			default:printf("Exception\n");
				break;
			}

			system("cls");
			system("mode con: cols=18 lines=30");
			Render();
			Position(character.x, character.y);
			printf("%s", character.shape);
		}

		if (CurrentTime != 0 && CurrentTime % level == 0)
		{

			if ('3' == map[character.y][character.x / 2])
			{
				score++;
				speed++;
				if (score > highscore)
					saveScore(score);
			}

			if ('2' == map[character.y][character.x / 2])
			{
				for (int i = 1; i < 8; i++)
				{
					if (line1 > line2 && hole1 != i)
						map[line1][i] = '1';
					else if (line1 > line2 && hole1 == i)
						map[line1][hole1] = '0';
					else if (line2 > line1 && hole2 != i)
						map[line2][i] = '1';
					else if (line2 > line1 && hole2 == i)
						map[line2][hole2] = '0';
				}
				if (defense == 0)
					health--;
				else if (defense == 1)
				{
					character.shape = "△";
					defense = 0;
				}
			}

			if ('4' == map[character.y][character.x / 2])
			{
				heartOn = 0;
				line3 = 1;
				if (health != 3)
					health++;
			}

			if ('5' == map[character.y][character.x / 2])
			{
				starOn = 0;
				line4 = 0;
				character.shape = "▲";
				defense = 1;
			}

			if (speed != 0 && speed % 3 == 0)
			{
				level -= 3;
				speed = 0;
			}

			if (heartOn == 0 && (item == 0 || item == 1))
			{
				heart = rand() % 7 + 1;
				heartOn = 1;
			}
			else if (defense == 0 && starOn == 0 && item == 2)
			{
				star = rand() % 7 + 1;
				starOn = 1;
			}

			if (heartOn == 1)
				line3++;

			if (starOn == 1)
				line4++;

			if (line3 >= 25)
			{
				line3 = 1;
				heartOn = 0;
			}

			if (line4 >= 25)
			{
				line4 = 1;
				starOn = 0;
			}

			system("cls");
			system("mode con: cols=18 lines=30");
			Render();
			Position(character.x, character.y);
			printf("%s", character.shape);
			line1++;
			line2++;
		}

		if (CurrentTime != 0 && CurrentTime % itemSpeed == 0)
			item = rand() % 10;

		if (health == 0)
			break;
	}

	system("cls");
	system("mode con: cols=18 lines=30");
	Sleep(1000);
	printf("----GAME OVER----\n");
	printf("score : %d\n\n", score);
	printf("%s\n", select[0]);
	while (1)
	{
		if (_kbhit())
		{
			key = _getch();

			if (key == -32)
			{
				key = _getch();
			}

			switch (key)
			{
			case UP: {
				system("cls");
				system("mode con: cols=18 lines=30");
				printf("----GAME OVER----\n");
				printf("score : %d\n\n", score);
				printf("%s\n", select[1]);
				again = 1;
				break;
			}
			case DOWN: {
				system("cls");
				system("mode con: cols=18 lines=30");
				printf("----GAME OVER----\n");
				printf("score : %d\n\n", score);
				printf("%s\n", select[2]);
				again = 2;
				break;
			}
			}

			if (again == 1 && GetAsyncKeyState(VK_SPACE) & 0x0001)
			{
				system("cls");
				system("mode con: cols=18 lines=30");
				score = 0;
				line1 = 1;
				line2 = 1;
				line3 = 1;
				line4 = 1;
				hole1 = 0;
				hole2 = 0;
				level = 200;
				health = 3;
				character.x = 8;
				character.y = 22;
				character.shape = "▲";
				heartOn = 0;
				starOn = 0;
				defense = 0;
				goto AGAIN;
			}
			else if (again == 2 && GetAsyncKeyState(VK_SPACE) & 0x0001)
				goto EXIT;
		}
	}

EXIT:

	return 0;
}
