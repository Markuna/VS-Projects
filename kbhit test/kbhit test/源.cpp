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

	system("pause");//输入缓冲队列，循环一次，输出一次。。。
	                //输入队列依次输入
	return 0;
}