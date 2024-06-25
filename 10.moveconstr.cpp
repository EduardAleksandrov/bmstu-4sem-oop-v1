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
    B() { cout << "const" << endl; }
    B(const B&) { cout << "copy const" << endl; }
    B(B&&) { cout << "move const" << endl; }
    void f() override { cout << "class B" << endl; }
    
};

B& g(B& x) { return x; }

int main()
{
    B b = B();
    g(b);
    return 0;
}