#include <iostream>

class One
{
private:
    int a;
protected:
    int b;
public:
    One(): a{5}, b{6} {}
    int f()
    {
        return a;
    }
};

class Two: private One
{
    private:    
        int c;
    protected:
        int t;
    public:
    Two(): c{7}, t{8} {}
    int g()
    {
        return b;
    }
};

int main()
{
    Two t;
    std::cout << t.g() << "\n";

    return 0;
}