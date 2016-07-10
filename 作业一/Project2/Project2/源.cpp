#include <iostream>
#include <cstring>
using namespace std;
class s
{
public:
	s() { *str = '\0'; }
	s(char *pstr)
	{
		strcpy_s(str, pstr);
	}
	char *gets() { return str; }
	s operator+(s obj);

private:
	char str[10];
};
s s::operator+(s obj)
{
	strcat_s(str, obj.str);
	return str;
}
int main()
{
	s obj1("Visual"), obj2(" C++"), obj3;
	obj3 = obj1 + obj2;
	cout << obj3.gets() << endl;
}
