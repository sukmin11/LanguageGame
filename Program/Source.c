#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

#define WIDTH 9
#define HEIGHT 25

int score = 0;
int speed = 0;
int hole1 = 0; 
int hole2 = 0;
int line1 = 1;
int line2 = 1;
int level = 200;
int health = 3;
int heart = 0;
int heartline = 1;
int heartOn = 0;
int heartspeed = 0;

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

void Render()
{
	if (map[line1][hole1] == '0' || map[line2][hole2] == '0')
	{
		score++;
		speed++;
	}

	if (map[line1][hole1] == '6' || map[line2][hole2] == '6')
	{
		health--;
	}

	if (speed != 0 && speed % 3 == 0)
	{
		speed = 0;
		level -= 10;
		heartOn = 1;
		heartspeed = rand() % 200 + 300;
	}

	for (int i = 0; i < 3; i++)
	{
		if(i < health)
		printf("♥");
		else
		printf("♡");
	}

	printf("\n");

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (map[i][j] == '0' || map[i][j] == '3' || map[i][j] == '4' || map[i][j] == '6')
				printf("  ");
			else if (map[i][j] == '1')
				printf("■");
			else if (map[i][j] == '2')
				printf("※");
			else if (map[i][j] == '5')
				printf("♥");
		}
		printf("\n");
	}
	printf("score : %d\n", score);
}

void Position(int x, int y)
{
	// X와 Y축을 설정하는 구조체입니다.
	COORD position = { x, y };

	// 콘솔 커서의 좌표를 설정하는 함수입니다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}


int main()
{
	srand(time(NULL));

	const char* select[3];

	select[0] = "Play Again?\nYES\nNO\n";
	select[1] = "Play Again?\nYES  ←\nNO\n";
	select[2] = "Play Again?\nYES\nNO   ←\n";

	int again = 0;
	char key = 0;
	
	Character character = { 8,22, "△"};

	AGAIN:

	hole1 = rand() % 7 + 1;

	for (int i = 1; i < 8; i++)
	{
		map[line1][i] = '2';
	}

	map[line1][hole1] = '3';

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
				map[line2][hole2] = '4';
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

			map[line2][hole2] = '4';
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

		if (heartOn == 1)
		{
			map[heartline][heart] = '5';
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

			Render();
			Position(character.x, character.y);
			printf("%s", character.shape);

		}

		if ('3' == map[character.y][character.x / 2])
		{
			map[line1][hole1] = '0';
		}
		else if ('4' == map[character.y][character.x / 2])
		{
			map[line2][hole2] = '0';
		}
		else if ('2' == map[character.y][character.x / 2])
		{
			for (int i = 1; i < 8; i++)
			{
				if (line1 > line2 && hole1 != i)
					map[line1][i] = '1';
				else if (line1 > line2 && hole1 == i)
					map[line1][hole1] ='6';
				else if (line2 > line1 && hole2 != i)
					map[line2][i] = '1';
				else if (line2 > line1 && hole2 == i)
					map[line2][hole2] = '6';
			}
		}

		if (CurrentTime != 0 && CurrentTime & heartspeed == 0)
			heartline++;

		if (CurrentTime != 0 && CurrentTime % level == 0)
		{
			system("cls");
			Render();
			Position(character.x, character.y);
			printf("%s", character.shape);
			line1++;
			line2++;	
		}

		if (health == 0)
			break;
	}

	system("cls");
	Sleep(500);
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
				printf("----GAME OVER----\n");
				printf("score : %d\n\n", score);
				printf("%s\n", select[1]);
				again = 1;
				break;
			}
			case DOWN: {
				system("cls");
				printf("----GAME OVER----\n");
				printf("score : %d\n\n", score);
				printf("%s\n", select[2]);
				again = 0;
				break;
			}
			}

			if (again == 1 && GetAsyncKeyState(VK_SPACE) & 0x0001)
			{
				system("cls");
				score = 0;
				line1 = 1;
				line2 = 1;
				hole1 = 0;
				hole2 = 0;
				level = 200;
				health = 3;
				goto AGAIN;
			}
			else if (again == 0 && GetAsyncKeyState(VK_SPACE) & 0x0001)
				goto EXIT;
		}
	}

EXIT:

	return 0;
}