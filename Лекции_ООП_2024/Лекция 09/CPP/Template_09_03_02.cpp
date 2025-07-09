# include <iostream>

using namespace std;

class A
{
public:
    A(int k, double d)
    {
        cout << "Calling the constructor of class A" << endl;
    }
};

class Creator
{
public:
    template<typename Type, typename... Args>
    static Type* create(Args&&... params)
    {
        return new Type(forward<Args>(params)...);
    }
};

void main()
{
    double d = 2.;
    A* p = Creator::create<A>(1, d);

    delete p;
}
