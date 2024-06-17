#include <iostream>
using namespace std;

template<typename Type>
class One
{
    Type X;
public:
    One(Type x): X{x}{}
    operator Type() // Getter
    { 
        cout << "operator" << endl;
        return X; 
    }
};

int main()
{   
    One t(5.5);

    double n = t;
    cout << t << endl;

    int i = 1;
    int&& rv2 = i+1;
    auto&& d5 = rv2;
    cout << d5 << endl;


    return 0;
}