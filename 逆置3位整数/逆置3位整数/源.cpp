//include
#include<iostream>

using namespace std;

void main()
{
	int number;
	int middle[3];
	char judge;

	again:;
	cout << "请输入三位整数" << endl;
	cin >> number;//键入

	if (number > 999 || number < 100)//判断是否是三位数
	{
		cout << "Error 是否重新输入【Y/N】";
		cin >> judge;
		if (judge == 'Y' || judge == 'y')
		{
			system("cls");
			goto again;
		}
		else
			while (judge !='Y' || judge !='y')
				return;
	}
	else
		//逆置过程
	{
		middle[2] = number / 100;
		middle[1] = number / 10 % 10;
		middle[0] = number % 10;
	}
	cout << middle[0] << middle[1] << middle[2] << endl;
	getchar();
	getchar();//未解决的问题：输入出现字符会直接出错退出
	          // 2016/3/12/18.27
}