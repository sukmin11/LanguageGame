#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE 10000

void Load(const char* filename)
{
	FILE* file = fopen(filename, "r");

	char buffer[SIZE] = { 0, };

	// ù ��° �Ű����� : ���� �����͸� ������ �޸� ������ ������ ����
	// �� ��° �Ű����� : �� ������ �׸��� ũ��
	// �� ��° �Ű����� : �����͸� �о�� ������ �׸��� ��
	// �� ���� �Ű����� : �����͸� �о�� ������ ������ ����

	fread(buffer, 1, SIZE, file);

	printf("%s", buffer);

	fclose(file);
}

int main()
{
#pragma region ���� �����

#pragma region ���� ����

	// ù ��° �Ű����� (������ �̸�)
	// �� ��° �Ű����� (������ ����� ���)
	FILE* file = fopen("data.txt", "w");
	
	fputs("Character Information\n", file);
	fputs("Health : \n", file);
	fputs("Attack : \n", file);
	fputs("Defense : \n", file);
	
	fclose(file);

#pragma endregion

#pragma region ���� �б�

	// Load("pokemon.txt");

#pragma endregion

#pragma endregion


	return 0;
}