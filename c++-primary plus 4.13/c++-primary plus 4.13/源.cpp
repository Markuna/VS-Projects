#include<iostream>
#include<string>

using namespace std;

struct CandyBar
{
	string pingpai;
	float weight;
	int calor;
};

int main()
{
	CandyBar snack;
	
	snack.pingpai = "Mocha Munch";
	snack.weight = 2.3l;
	snack.calor = 350;

	cout << snack.pingpai << "\n" << snack.weight << "\n" << snack.calor << endl;

	system("pause");
	return 0;
}