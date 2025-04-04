#include <iostream>

class One {
public:
    virtual void start()=0;
};

class Two : public One 
{
public:
    void start() override
    {
        std::cout << "start from two" << "\n";
    }
    void start_two()
    {
        std::cout << "start_two from two" << "\n";
    }
};


int main()
{
    One* th = new Two();
    th->start();
    
    Two* thnew = dynamic_cast<Two*>(th);
    thnew->start_two();

    return 0;
}