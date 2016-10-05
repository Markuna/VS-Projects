#include<iostream>
using namespace std;
#define square(x) ((x)*(x))//宏定义，尤其注意括号，不加括号会出现不可预见的错误

//内联函数，替换主函数部分，提高运行效率//比子函数效率高
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