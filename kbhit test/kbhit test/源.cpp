#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>

int main()
{

	char ch='a';

	while (1)
	{
		Sleep(250);

		if (_kbhit())
		{
			ch = getchar();
			if (ch == 'b')
			{
				printf("hit b\n");
			}
		}
	}
	printf("not get in while \n");

	system("pause");//���뻺����У�ѭ��һ�Σ����һ�Ρ�����
	                //���������������
	return 0;
}