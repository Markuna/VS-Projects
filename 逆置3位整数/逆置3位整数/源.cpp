//include
#include<iostream>

using namespace std;

void main()
{
	int number;
	int middle[3];
	char judge;

	again:;
	cout << "��������λ����" << endl;
	cin >> number;//����

	if (number > 999 || number < 100)//�ж��Ƿ�����λ��
	{
		cout << "Error �Ƿ��������롾Y/N��";
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
		//���ù���
	{
		middle[2] = number / 100;
		middle[1] = number / 10 % 10;
		middle[0] = number % 10;
	}
	cout << middle[0] << middle[1] << middle[2] << endl;
	getchar();
	getchar();//δ��������⣺��������ַ���ֱ�ӳ����˳�
	          // 2016/3/12/18.27
}