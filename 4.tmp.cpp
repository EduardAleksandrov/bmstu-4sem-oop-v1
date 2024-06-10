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

template<typename T>
class Dog
{
public:
    template<typename S>
    void Lay(T x, S y);
};

template<typename T>
template<typename S>
    void Dog<T>::Lay(T x, S y) { std::cout << x << " " << y << std::endl; }

template class Dog<int>; // явное создание шаблона для Dog типа int
//---------------
template<typename T>
struct Type2Type
{
    using type = T;
};
//---------------

// A generic function which finds minimum of two values
// return type is type of variable which is minimum
template <class A, class B>
auto findMin(A a, B b) -> decltype(a < b ? a : b)
{
    return (a < b) ? a : b;
}
//---------------

template<typename...Args>
auto sum(Args...args) 
{ 
    auto s = (args+...);
    return s; 
}

//---------------
void data()
{
    auto n {0}; // auto работает на этапе компиляции
    std::cin >> n;
    std::cout << n << std::endl;
}

//---------------

int main(void)
{
    g(5.5);

    f(new Pool());

    
    Dog<int> dog;
    dog.template Lay<int>(1, 5);


    // This call returns 3.44 of double type
    std::cout << findMin(4, 3.44) << std::endl;
    // This call returns 3 of double type
    std::cout << findMin(5.4, 3) << std::endl;


    std::cout << sum(1,2,3,4.05) << std::endl;

    data();

    return 0;
}