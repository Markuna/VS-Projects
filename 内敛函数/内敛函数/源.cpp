#include<iostream>
using namespace std;
#define square(x) ((x)*(x))//�궨�壬����ע�����ţ��������Ż���ֲ���Ԥ���Ĵ���

//�����������滻���������֣��������Ч��//���Ӻ���Ч�ʸ�
inline bool except(int a,int b)
{
	bool e;
	e=a > b ? true : false;
	return e;
}

int main()
{
	int e;
	e = square(2 + 1);
	cout << e << endl;

	cout << except(6, e) << endl;

	system("pause");

	return 0;
}