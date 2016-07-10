//include
#include<stdio.h>
#include<iostream>

using namespace std;

struct inds {
	char name[20];
	float volum;
	double price;
};

void main()
{
	char ch;
	int count = 0;
	cout << "ent\n";
	cin.get(ch);
	while (ch != '#')
	{
		cout << ch;
		++count;
		cin.get(ch);
	}
	cout << endl << count << " characters read\n";
	
	getchar();
	getchar();
}