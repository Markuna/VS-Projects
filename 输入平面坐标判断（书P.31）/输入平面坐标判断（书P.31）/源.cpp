#include<iostream>;

using namespace std;

double x, y;//ȫ�ֱ���

void check()//����
{
	cout << "��������" << endl;
	cout << "x="; cin >> x;
	cout << "y="; cin >> y;
}

void judge()//�жϲ����
{
    if ((x>-2.0&&x< 2.0 )&&( y>-2.0&&y < 2.0))
	//if(-2.0<x<2&&-2.0<y<2.0)  ʵ�ֲ��ˡ���������ǰ������
		cout << "1" << endl;
	else
		cout << "0" << endl;
}

void main()
{
	check();
	judge();
	getchar();
	getchar();//  2016/3/12 19.55
}