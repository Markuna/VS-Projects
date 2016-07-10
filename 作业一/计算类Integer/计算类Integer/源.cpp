#include<iostream>
using namespace std;
class Integer
{
private:
	short int a;
public:
	Integer();
	Integer(short int b);
	Integer operator+(Integer &t);
	Integer operator-(Integer t);
	Integer operator*(Integer t);
	Integer operator/(Integer t);
	Integer operator=(Integer &t);
	void show();
};

void check(short &n)
{
	if (n > 30000 || n < -30000) { cout << "Òç³öerror" << endl; }
}

Integer::Integer()
{
	a = 0;
}

Integer::Integer(short int b)
{
	a = b;
}

Integer Integer::operator+(Integer &t)
{
	Integer temp;
	temp.a = a + t.a;
	check(temp.a);
	return temp;
}

Integer Integer::operator-(Integer t)
{
	Integer temp(0);
	temp.a = a - t.a;
	check(temp.a);
	return temp;
}

Integer Integer::operator*(Integer t)
{
	Integer temp(0);
	temp.a = a * t.a;
	check(temp.a);
	return temp;
}

Integer Integer::operator/(Integer t)
{
	Integer temp(0);
	temp.a = a / t.a;
	check(temp.a);
	return temp;
}

Integer Integer::operator=(Integer &t)
{
    a = t.a;
	check(a);
	return *this;
}

void Integer::show()
{
	cout << a << endl;
}

void main()
{
	Integer a(50), b(20), c;
	c = a + b;
	c.show();

	c = a - b;
	c.show();

	c = a*b;
	c.show();

	c = a / b;
	c.show();

	system("pause");
}