#include <iostream>
#include <exception>

class My_except: public std::exception
{
private:
    std::string ex;
public:
    explicit My_except(std::string e):ex{e} {}
    std::string ex_happend() const
    {
        return ex;
    }
};

void trigger()
{
    throw My_except("It(exception) happend");
}

int main()
{
    try
    {
        trigger();
    }
    catch(const My_except& e)
    {
        std::cerr << e.ex_happend() << '\n';
    }
    return 0;
}
