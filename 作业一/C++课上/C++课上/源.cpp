#include<iostream>
class Student
{
	double score;
	static double total;
	static int cout;
public:
	void scoretotalcount(double s)
	{
		score = s;
		total = total + s;
		cout++;
	}
	static double sum()
	{
		printf("总分=%f\n", total);
		return total;
	}
	static void average()
	{
		double aver;
		aver = total / cout;
		printf("平均数=%f\n", aver);
	}
};
double Student::total = 0.0;
int Student::cout = 0;

void main()
{
	Student shichenghao, SB;
	shichenghao.scoretotalcount(59.9);
	SB.scoretotalcount(60.0);
	Student::sum();
	Student::average();
}