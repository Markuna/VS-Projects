#include<iostream>
using namespace std;

const int MAX = 500;

void chack()
{

}

class Strg
{

private:
	char mdata[MAX];

public:
	Strg();
	Strg(char *a);
	void show();
	friend Strg operator+(Strg &t);

};

Strg::Strg()
{
	//strcpy(mdata, data);
}

//���غ���
Strg::Strg(char *a)
{
	strcpy(mdata, a);
}

//���ؼӷ�����
Strg operator+(Strg &t)
{
	char *data;
	*data = mdata;
	strcat(*data, t);
	return Strg();
}

//���
void Strg::show()
{
	cout << mdata << endl;
}

void main()
{
	char x[10] = "Native!";
	char y[10] = "����";

	Strg a(x), b(y);
	Strg c;

	c = a + b;

	c.show();
}