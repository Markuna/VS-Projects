#include<iostream>;

using namespace std;

double x, y;//全局变量

void check()//输入
{
	cout << "输入坐标" << endl;
	cout << "x="; cin >> x;
	cout << "y="; cin >> y;
}

void judge()//判断并输出
{
    if ((x>-2.0&&x< 2.0 )&&( y>-2.0&&y < 2.0))
	//if(-2.0<x<2&&-2.0<y<2.0)  实现不了。。变量在前。。。
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