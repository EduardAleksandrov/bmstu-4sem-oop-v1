# include <iostream>

using namespace std;

class A
{
public:
	virtual ~A() = 0;
};

A::~A() = default;

class B : public A
{
public:
	virtual ~B() override { cout << "Class B destructor called;" << endl; }
};

void main()
{
	A* pobj = new B;

	delete pobj;
}
