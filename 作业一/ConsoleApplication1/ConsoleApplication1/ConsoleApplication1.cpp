// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main()
{
    return 0;
}

#include <iostream>
using namespace std;
class student
{
public:
	void scoretotalcount(double s)
	{
		score = s;
		total = total + score;
		count++;
	}
	static double sum()
	{
		return total;
	}
	static double average()
	{
		return total / count;
	}
private:
	double  score;
	static double total;
	static double count;
};
double student::total = 0;
double student::count = 0;
int main()
{
	int i, n; double s;
	cout << "请输入学生人数：";
	cin >> n;
	student  stu;
	for (i = 1; i <= n; i++)
	{
		cout << "请输入第" << i << "个学生的分数：";
		cin >> s;
		stu.scoretotalcount(s);
	}
	cout << "总分：" << student::sum() << endl;
	cout << "平均分：" << student::average() << endl;
}
