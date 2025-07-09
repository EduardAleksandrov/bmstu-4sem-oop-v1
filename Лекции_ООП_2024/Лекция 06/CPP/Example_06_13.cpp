# include <iostream>

using namespace std;

class A // abstract
{
public:
	virtual void f() = 0;
};

class B : public A
{
public:
	void f() override { cout << "Executing f from B;" << endl; }
};

class C
{
public:
	static void g(A& obj) { obj.f(); }
};

void main()
{
	B obj;

	C::g(obj);
}
