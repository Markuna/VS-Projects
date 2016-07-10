#include <iostream>
using namespace std;
class rectangle
{
public:
	rectangle(double l, double w)
	{
		length = l; width = w;
	}
	double area()
	{
		return(length*width);
	}
	double getlength()
	{
		return length;
	}
	double getwidth()
	{
		return width;
	}
private:
	double length;
	double width;
};
class rectangular :public rectangle
{
public:
	rectangular(double l, double w, double h) : rectangle(l, w)
	{
		height = h;
	}
	double getheight()
	{
		return height;
	}
	double volume()
	{
		return area() *height;
	}
private:
	double height;
};
int main()
{
	rectangle obj1(1, 2);
	rectangular obj2(3, 4, 5);
	cout << "��=" << obj1.getlength() << '\t' << "��=" << obj1.getwidth() << endl;
	cout << "���=" << obj1.area() << endl;
	cout << "��=" << obj2.getlength() << '\t' << "��=" << obj2.getwidth();
	cout << '\t' << "��=" << obj2.getheight() << endl;
	cout << "���=" << obj2.volume() << endl;
	system("pause");
}
