#include <iostream>
#include <memory> 
#include <vector>

using namespace std;
namespace
{
    struct A 
    { 
        int X = 4;
        A() = default;
        A(int x) { X = x; }
        void printA() { cout << "A struct...." << X << endl; } 
    }; 
}


int main()
{
    int x =5;
    unique_ptr<int> p1(make_unique<int>(x)); 
    cout << *p1 << endl;

    unique_ptr<A> p2(make_unique<A>()); // make создаем объект в динамической памяти
    p2->printA();

    vector<unique_ptr<A>> v;
    v.push_back(make_unique<A>(5));
    v[0]->printA();

    std::shared_ptr<A> b = make_shared<A>();
    std::weak_ptr<A> bb(b);
    // b.reset();
    std::cout << bb.expired() << std::endl;


    return 0;
}