#include<iostream>
using namespace std;
class Rectangle
{
public:
	double length;            //��
	double width;             //��
	void mianji();
};

class Rectangular :public Rectangle
{
public:
	double heigh;             //��
	void tiji();
};

void Rectangle::mianji()
{
	double mianji;
	mianji = length*width;
	cout <<"���Ϊ��"<< mianji << endl;
}

void Rectangular::tiji()
{
	double tiji;
	tiji = heigh*length*width;
	cout <<"���Ϊ��"<< tiji << endl;
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