#include <iostream>
using namespace std;
# include <string>
class A {
public:
	virtual void fun1() { cout << "Class A\n"; }
};
class B : public A {
public:
	void fun1(int y = 0) { cout << "Class B\n"; }
};
class C : public B {
public:
	virtual void fun1() { cout << "Class C\n"; }
};
void main() {
	A *pa, a;
	B *pb, b;
	C c;
	pa = &a;       //1
	pa->fun1();
	pa = &b;       //2
	pa->fun1();
	pb = &c;       //3
	pb->fun1();    //confuse me ... why B ?

	system("pause");
}
