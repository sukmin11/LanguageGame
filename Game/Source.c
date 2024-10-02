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
			if (map[y + i][x + j] == '2' || map[y + i][x + j] == '4')
				number++;
	}

	return number;
}

void Render(int a, int b)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (map[i][j] == '0') // 0: 공백, 2: 지뢰
			{
				if (i == b && j == a)
					setColor(3, 0);
				printf("□");
				setColor(7, 0);
			}
			else if (map[i][j] == '1') // 벽
			printf("■");
			else if(map[i][j] == '2')
			{
				setColor(4, 0);
				printf("※");
				setColor(7, 0);
			}
			else if (map[i][j] == '3' || map[i][j] == '4') // 깃발
			{
				setColor(7, 4);
				if (i == b && j == a)
					setColor(3, 4);
				printf("□");
				setColor(7, 0);
			}
			else if(map[i][j] == '5') // 지뢰
			{
				setColor(4, 0);
				printf("※");
				setColor(7, 0);
			}
			else if (map[i][j] == 0)
			{
				setColor(0, 0);
				if (i == b && j == a)
					setColor(3, 0);
				printf("□");
				setColor(7, 0);
			}
			else if (map[i][j] == 1)
			{
				if (i == b && j == a)
					setColor(3, 0);
				printf(" 1");
				setColor(7, 0);
			}
			else if (map[i][j] == 2)
			{
				if (i == b && j == a)
					setColor(3, 0);
				printf(" 2");
				setColor(7, 0);
			}
			else if (map[i][j] == 3)
			{
				if (i == b && j == a)
					setColor(3, 0);
				printf(" 3");
				setColor(7, 0);
			}
			else if (map[i][j] == 4)
			{
				if (i == b && j == a)
					setColor(3, 0);
				printf(" 4");
				setColor(7, 0);
			}
			else if (map[i][j] == 5)
			{
				if (i == b && j == a)
					setColor(3, 0);
				printf(" 5");
				setColor(7, 0);
			}
			else if (map[i][j] == 6)
			{
				if (i == b && j == a)
					setColor(3, 0);
				printf(" 6");
				setColor(7, 0);
			}
			else if (map[i][j] == 7)
			{
				if (i == b && j == a)
					setColor(3, 0);
				printf(" 7");
				setColor(7, 0);
			}
			else if (map[i][j] == 8)
			{
				if (i == b && j == a)
					setColor(3, 0);
				printf(" 8");
				setColor(7, 0);
			}
		}
		printf("\n");
	}
	printf("지뢰 : %d\n", bomb);
}

typedef struct Character {

	int x; 
	int y;
}Character;

void Position(int x, int y)
{
	// X와 Y축을 설정하는 구조체입니다.
	COORD position = { x, y };

	// 콘솔 커서의 좌표를 설정하는 함수입니다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int clear()
{
	int clear = 0;

	for (int i = 1; i < HEIGHT - 1; i++)
	{
		for (int j = 1; j < WIDTH - 1; j++)
		{
			if (map[i][j] != '0' && map[i][j] != '2' && map[i][j] != '3' && map[i][j] != '4')
				clear++;
		}
	}

	return clear;
}

int main()
{
	char key = 0; 

	Character character = { 30, 8 };
	
	srand(time(NULL));

	Shuffle();

	Render(character.x / 2, character.y);

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

			Render(character.x / 2, character.y);
			Position(character.x, character.y);
		}

		if ((GetAsyncKeyState(VK_SPACE) & 0x0001) && map[character.y][character.x / 2] != '3' && map[character.y][character.x / 2] != '4')
		{
			if (map[character.y][character.x / 2] == '0')
			{
				map[character.y][character.x / 2] = number(character.x / 2, character.y);
			}
			else if (map[character.y][character.x / 2] == '2')
			{
				for (int i = 1; i < HEIGHT - 1; i++)
					for (int j = 1; j < WIDTH - 1; j++)
						if (map[i][j] == '2')
							map[i][j] = '5';
				system("cls");
				Render(character.x / 2, character.y);
				break;
			}
		}

		for (int a = 1; a < HEIGHT - 1; a++)
		{
			for(int b = 1; b < WIDTH - 1; b ++)
				if(map[a][b] == 0)
					for (int i = -1; i <= 1; i++)
					{
						for (int j = -1; j <= 1; j++)
							if (map[a + i][b + j] != '2' && map[a + i][b + j] != '4' && map[a + i][b + j] != '1')
							{
								if (number(b + j, a + i) == 0)
									map[a + i][b + j] = 0;
								else if (number(b + j, a + i) == 1)
									map[a + i][b + j] = 1;
								else if (number(b + j, a + i) == 2)
									map[a + i][b + j] = 2;
								else if (number(b + j, a + i) == 3)
									map[a + i][b + j] = 3;
							}
					}
		}

		if (GetAsyncKeyState(VK_SHIFT) & 0x0001)
		{
			if (map[character.y][character.x / 2] == '0')
			{
				bomb--;
				map[character.y][character.x / 2] = '3';
				system("cls");
				Render(character.x / 2, character.y);
			}
			else if (map[character.y][character.x / 2] == '2')
			{
				bomb--;
				map[character.y][character.x / 2] = '4';
				system("cls");
				Render(character.x / 2, character.y);
			}
			else if (map[character.y][character.x / 2] == '3')
			{
				bomb++;
				map[character.y][character.x / 2] = '0';
				system("cls");
				Render(character.x / 2, character.y);
			}
			else if (map[character.y][character.x / 2] == '4')
			{
				bomb++;
				map[character.y][character.x / 2] = '2';
				system("cls");
				Render(character.x / 2, character.y);
			}
		}

		if (clear() == 8 * 28)
			break;
	}



	return 0;
}