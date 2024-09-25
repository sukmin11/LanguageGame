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
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (map[i][j] == '0')
				printf("  ");
			else if (map[i][j] == '1')
				printf("■");
			else if (map[i][j] == '2')
				printf("※");
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

	AGAIN:

	int hole1 = 0; 
	int hole2 = 0;
	int line1 = 1;
	int line2 = 1;
	char key = 0;

	Character character = { 8,22, "△"};

	hole1 = rand() % 7 + 1;

	for (int i = 1; i < 8; i++)
	{
		map[line1][i] = '2';
	}

	map[line1][hole1] = '0';

	Render();
	
	while (1)
	{

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
			map[line1][hole1] = '0';
		}

		if (line1 != line2)
		{
			for (int i = 1; i < 8; i++)
			{
				map[line2][i] = '2';
				map[line2][hole2] = '0';
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

			map[line2][hole2] = '0';
		}

		if (line2 == 15)
		{
			line1 = 1;
			hole1 = rand() % 7 + 1;
			for (int i = 1; i < 8; i++)
			{
				map[line1][i] = '2';
			}

			map[line1][hole1] = '0';
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

		if (map[line1][hole1] == map[character.y][character.x / 2] || map[line2][hole2] == map[character.y][character.x / 2])
			score++;


		Sleep(100);
		system("cls");
		Render();
		Position(character.x, character.y);
		printf("%s", character.shape);
		line1++;
		line2++;
		
		if (map[character.y][character.x / 2] == '2')
			break;
	}

	system("cls");
	Sleep(500);
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
				printf("score : %d\n\n", score);
				printf("%s\n", select[1]);
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					goto AGAIN;
				break;
			}
			case DOWN: {
				system("cls");
				printf("score : %d\n\n", score);
				printf("%s\n", select[2]);
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					goto EXIT;
				break;
			}
			}
		}
	}

EXIT:
	printf("GAME OVER\n");

	return 0;
}