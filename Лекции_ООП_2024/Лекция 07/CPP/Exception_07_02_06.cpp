# include <iostream>
# include <exception>

using namespace std;

class A
{
private:
    A(int d) // noexcept
    {
        if (d < 0)
            throw std::runtime_error("Error!");
    }

public:
    ~A() noexcept(false) // деструктор по умолчанию noexcept(true)
    {
        throw std::runtime_error("Destructor");
    }

    static A create(int v);
};

A A::create(int v) noexcept(noexcept(A(v)))
{
    return A(v);
}

int main()
{
    try
    {
        A obj = A::create(-5);
    }
    catch (const std::runtime_error& err)
    {
        cout << err.what() << endl;
    }
}

