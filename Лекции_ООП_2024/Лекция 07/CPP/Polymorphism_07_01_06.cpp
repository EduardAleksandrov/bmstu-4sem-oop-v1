# include <iostream>

using namespace std;

class A
{
public:
	virtual ~A() = default;
	virtual void f() = 0;
};

class B : public A
{
	int b;

public:
	void f() override { cout << "Executing f from B;" << endl; }
};

class C
{
public:
	static A& index(A* p, int i) { return p[i]; }
};

void main()
{
	const int N = 10;
	B vect[N];
	A& alias = C::index(vect, 5);

	alias.f();  // Error!!!
}
