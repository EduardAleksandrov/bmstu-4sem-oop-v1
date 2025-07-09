# include <iostream>

using namespace std;

class A
{
public:
    A() { cout << "  Default constructor" << endl; }
    A(const A&) { cout << "  Copy constructor" << endl; }
    A(A&&) noexcept { cout << "  Move constructor" << endl; }
    ~A() { cout << "  Destructor" << endl; }
};

A f(A obj) { return obj; }

A f1() { return A(); }

A f2()
{
    A obj;

    return obj;
}

int main()
{
    cout << "prim 1" << endl;
    {
        A obj;

        f(obj);
    }
    cout << "prim 2" << endl;
    {
        A obj = f1();
    }
    cout << "prim 3" << endl;
    {
        A obj = f2();
    }
}
