# include <iostream>

using namespace std;

class C; // forward объявление

class A
{
protected:
	virtual void f() { cout << "Executing f from A;" << endl; }

	friend C;
};

class B : public A
{
protected:
	void f() override { cout << "Executing f from B;" << endl; }
};

class C
{
public:
	static void g(A& obj) { obj.f(); }
};

void main()
{
	B bobj;

	C::g(bobj);
}
