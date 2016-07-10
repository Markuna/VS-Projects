#include <iostream>
#include<cstring>
using namespace std;
class s
{
public:
   s() 
    { 
	*str = '\0'; 
    }
	s(char *pstr) 
	{ 
		strcpy_s(str, pstr); 
	}
	char *gets() 
	{ 
		return str; 
	}
	friend s operator+(s obj1, s obj2);
private:
	char str[100];
};
s operator+(s obj1, s obj2)
{
	s tempobj;
	strcat_s(tempobj.str, obj1.str);
	strcat_s(tempobj.str, obj2.str);
	return tempobj;
}
int main()
{
	s obj1("HAHAHAHA"), obj2("¸ò¸ò¸ò"), obj3;
	obj3 = obj1 + obj2;
	cout << obj3.gets() << endl;

	system("pause");
}
