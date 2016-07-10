#include<iostream>
using namespace std;
class Rectangle
{
public:
	double length;            //长
	double width;             //宽
	void mianji();
};

class Rectangular :public Rectangle
{
public:
	double heigh;             //高
	void tiji();
};

void Rectangle::mianji()
{
	double mianji;
	mianji = length*width;
	cout <<"面积为："<< mianji << endl;
}

void Rectangular::tiji()
{
	double tiji;
	tiji = heigh*length*width;
	cout <<"体积为："<< tiji << endl;
}

void main()
{
	Rectangular a1;
	a1.length = 10.2;
	a1.width = 20.0;
	a1.heigh = 30.5;

	a1.mianji();
	a1.tiji();

	system("pause");
}