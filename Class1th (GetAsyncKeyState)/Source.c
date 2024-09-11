#include <stdio.h>
#include <time.h>
#include <windows.h>

#define SIZE 10

void Shuffle(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int seed = rand() % size;

		int temporary = array[seed];

		array[temporary] = array[i];

		array[i] = temporary;
	}
}

int main()
{
#pragma region 셔플 함수

	// srand(time(NULL));
	// 
	// int list[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	// 
	// int size = sizeof(list) / sizeof(int);
	// 
	// Shuffle(list, size);
	// 
	// for (int i = 0; i < size; i++)
	// {
	// 	printf("list[%d]의 값 : %d\n", i, list[i]);
	// }

#pragma endregion

#pragma region 포인터 배열

	// const char* dialog[SIZE];
	// 
	// dialog[0] = "안녕하세요?";
	// dialog[1] = "누구신가요?";
	// dialog[2] = "탐정입니다.";
	// dialog[3] = "의뢰인입니다.";
	// dialog[4] = "수상한 사건있다고 해서 왔습니다.";
	// dialog[5] = "네 맞습니다";
	// dialog[6] = "이 사건에 대해 아시는 게 있나요?";
	// dialog[7] = "조금 알고 있습니다.";
	// dialog[8] = "말씀해주세요.";
	// dialog[9] = "..........";
	// 
	// int i = 0;
	// 
	// while (i < SIZE)
	// {
	// 	// 0x0000 : 이전에 누른 적이 없고 호출 시점에도 눌려있지 않은 상태
	// 
	// 	// 0x0001 : 이전에 누른 적이 있고 호출 시점에는 눌려있지 않은 상태
	// 
	// 	// 0x8000 : 이전에 누른 적이 없고 호출 시점에는 눌려있는 상태
	// 
	// 	// 0x8001 : 이전에 누른 적이 있고 호출 시점에도 눌려있는 상태
	// 
	// 	//              0x20           & 0x0001
	// 	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	// 	{
	// 		if (i % 2 == 0)
	// 		{
	// 			printf("탐정 : %s\n", dialog[i]);
	// 		}
	// 		else
	// 		{
	// 			printf("의뢰인 : %s\n", dialog[i]);
	// 		}
	// 
	// 		i++;
	// 	}
	// }
	// 
	// Sleep(3000);
	// 
	// printf("대화가 종료되었습니다.\n"); 

#pragma endregion


	return 0;
}