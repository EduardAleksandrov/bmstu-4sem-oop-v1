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

    return 0;
}