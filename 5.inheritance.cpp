#include <iostream>

using namespace std;

class A
{
public:
    virtual void f() { cout << "class A" << endl; }
};

class B: public A
{
public:
    B() { A::f(); f(); }
    B(const B&) { cout << "copy const" << endl; }
    B(B&&) { cout << "move const" << endl; }
    void f() override { cout << "class B" << endl; }
    
};

B g(B x) { return x; }

int main()
{
    A* p = new B();
    p->f();
    B* t = static_cast<B*>(p);
    B* tt = dynamic_cast<B*>(p); // класс должен быть полиморфным
    t->f();
    tt->f();
    delete p;
    cout << (p == t) << endl;

    B obj;
    g(obj);
    return 0;
}