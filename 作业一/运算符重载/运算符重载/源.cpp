#include<iostream>
using namespace std;
class nchar
{
private:
	static int slen;               //�ۼ����ж�����ĳ���
	int len;                       //��ǰ�ַ�����
	char sout[];
public:
	void str(char s[]="")
	{
		//slen = slen + strlen(s);           //��ȡ����
		slen = strlen(s);
		int i;
		len = strlen(s);
		for (i = 0; i < len; i++)  //��S���Ƶ�sout
		{
			sout[i] = s[i];
		}
		//sout[i] = '\0';
	}
	nchar operator+(nchar t)
	{
		int i;
		nchar temp;
		for (i = 0; i < slen && (t.sout[i]) != '\0'; i++)
		{
			temp.sout[len] = t.sout[i];
			len++;
		}
		return temp;
	}
	nchar &nchar::operator=(nchar t)
	{
		int i;
		for (i = 0; i < slen && (t.sout[i]) != '\0'; i++)
		{
			sout[i] = t.sout[i];
		}
		return *this;
	}
	void show()
	{
		cout << sout << endl;
	}

};

int nchar::slen = 0;

void main()
{
	nchar a1;
	nchar a2;
	a1.str ("How are you?");
	a2.str ("How old are you? hey, fuck you guy.");
	nchar c1;

	c1 = a1 + a2;

	c1.show();

	a1.show();
	a2.show();

	getchar();
	                                             //error
}