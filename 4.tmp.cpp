#include <iostream>
//---------------
void f(int x)
{
    std::cout << "int" << std::endl;
}

void f(double x)
{
    std::cout << "double" << std::endl;
}

template <typename T>
void g(T t)
{
    f(t);
}
//---------------
class Pool
{
public:
    template<typename T> T get(T x) { return x; }
};

template<typename Alloc>
void f(Alloc all)
{
    int p1 = all->template get<int>(5);
    
    std::cout <<  "p1 " << p1 << std::endl;
    
    delete all;
    all = nullptr;
}
//---------------

int main(void)
{
    g(5.5);

    f(new Pool());
    return 0;
}