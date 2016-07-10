#include<iostream>

using namespace std;

void main()
{
	int z,x,c;
	int min;
	cout << "输入三个整数" << endl;
	
	cin >>z>>x>>c;
	min = z < x ? (z < c ? z : c) : (x < c ? x : c);
	cout << min << endl;

	getchar();
	getchar();//  2016/3/12  20.27
}