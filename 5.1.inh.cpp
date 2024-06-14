#include <iostream>
using namespace std;
 
class Base {
    
public:
    int x;
 
    // parameterized constructor
    Base(int a) : x(a){ cout << "Base constructor" << endl;};
};
 
class Derived : public Base {
public:
    using Base::Base; //авто конструктор+доступ к членам
    int y;
    // Derived(int n): Base(n) {Base::x = 2;}
};
 
int main()
{
 
    Derived d(42);
    // d.y = 12;
    cout << d.x << " " << d.y << '\n';
 
    return 0;
}