#include <iostream>

using namespace std;

class A
{
    const int x = 3;
public:
    virtual void f() { cout << "class A" << endl; }
};

class B: public A
{
public:
    B() { cout << "const" << endl; }
    B(const B&) { cout << "copy const" << endl; }
    B(B&&) { cout << "move const" << endl; }
    void f() override { cout << "class B" << endl; }
    
};

class C
{

};

B& g(B& x) { return x; }

A& index(A** obj, int i) { return *obj[i]; }

int main()
{
    B b = B();
    g(b);

    A* mas[3];
    mas[0] = new B();
    mas[1] = new B();
    mas[2] = new B();
    A& a = index(mas, 2); 
    a.f();


    return 0;
}