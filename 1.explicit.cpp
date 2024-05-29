#include <iostream>

class Array
{
private:
    double* arr;
    int count;
public:
    explicit Array(int cnt): count{cnt}
    {
        arr = new double[count];
        std::cout << "вызов костр" << std::endl;
    }
    Array() = default;
    int operator[](int index)
    {
        return arr[index];
    }
    ~Array()
    {
        std::cout << "вызов дестр" << std::endl;

        delete[] arr;
        arr = nullptr;
    }
};


int main()
{
    Array a(4);
    // for(int i = 0; i<10; i++)
    //     std::cout << a[i] << std::endl;
    // std::cout<<std::endl;
    a=5; //при explicit дает ошибку
    for(int i = 0; i<10; i++)
        std::cout << a[i] << std::endl;
    return 0;
}