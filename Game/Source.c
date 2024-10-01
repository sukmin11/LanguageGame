#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT 15
#define WIDTH 30

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

int bomb = 140;
int rand_height;
int rand_width;

char map[HEIGHT][WIDTH] = {
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
	{'1','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','1'},
	{'1','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','1'},
	{'1','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','1'},
	{'1','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','1'},
	{'1','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
};

void setColor(int textColor, int bgColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, textColor | (bgColor << 4));
}

void Shuffle()
{
	srand(time(NULL));

	for (int i = 1; i < HEIGHT - 1; i++)
	{
		for (int j = 1; j < WIDTH - 1; j++)
		{
			rand_height = rand() % 13 + 1;
			rand_width = rand() % 28 + 1;

			char temporary = map[rand_height][rand_width];

			map[rand_height][rand_width] = map[i][j];

			map[i][j] = temporary;
		}
	}
}

int number(int x, int y)
{
	int number = 0;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
			if (map[y + i][x + j] == '2')
				number++;
	}

	return number;
}

void Render()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (map[i][j] == '0')
				printf("  ");
			else if (map[i][j] == '1')
				printf("■");
			else if (map[i][j] == '2')
				printf("□");
			else if (map[i][j] == '3')
				printf("＠");
			else if (map[i][j] == 0)
				printf("  ");
			else if (map[i][j] == 1)
				printf(" 1");
			else if (map[i][j] == 2)
				printf(" 2");
			else if (map[i][j] == 3)
				printf(" 3");
			else if (map[i][j] == 4)
				printf(" 4");
			else if (map[i][j] == 5)
				printf(" 5");
			else if (map[i][j] == 6)
				printf(" 6");
			else if (map[i][j] == 7)
				printf(" 7");
			else if (map[i][j] == 8)
				printf(" 8");
		}
		printf("\n");
	}
	printf("지뢰 : %d\n", bomb);
}

typedef struct Character {

	int x; 
	int y;
	const char* shape;
}Character;

void Position(int x, int y)
{
	// X와 Y축을 설정하는 구조체입니다.
	COORD position = { x, y };

	// 콘솔 커서의 좌표를 설정하는 함수입니다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int main()
{
	char key = 0; 

	Character character = { 30, 8, "□" };
	
	srand(time(NULL));

	Shuffle();

	Render();

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
			case UP:
				if (map[character.y - 1][character.x / 2] != '1')
				{
					character.y--;
				}
				break;
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
			case DOWN:
				if (map[character.y + 1][character.x / 2] != '1')
				{
					character.y++;
				}
				break;
			default:
				break;
			}

			system("cls");

			Render();
			Position(character.x, character.y);
			printf("%s", character.shape);
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x0001)
		{
			if (map[character.y][character.x / 2] == '0')
				map[character.y][character.x / 2] = number(character.x / 2, character.y);
			else if (map[character.y][character.x / 2] == '2')
				break;
		}
		if (GetAsyncKeyState(VK_SHIFT) & 0x0001)
			if (map[character.y][character.x / 2] == '0' || map[character.y][character.x / 2] == '2')
			{
				bomb--;
				map[character.y][character.x / 2] = '3';
			}
	}
	return 0;
}