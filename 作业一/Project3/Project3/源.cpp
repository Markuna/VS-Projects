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
	cout << "长=" << obj1.getlength() << '\t' << "宽=" << obj1.getwidth() << endl;
	cout << "面积=" << obj1.area() << endl;
	cout << "长=" << obj2.getlength() << '\t' << "宽=" << obj2.getwidth();
	cout << '\t' << "高=" << obj2.getheight() << endl;
	cout << "体积=" << obj2.volume() << endl;
	system("pause");
}
