#include <iostream>

using namespace std;

class Person
{
public:
    Person(std::string name): name{name}
    { }
    virtual void print() const  // виртуальная функция
    {
        std::cout << "Name: " << name << std::endl;
    }
private:
    std::string name;
};
class Employee: public Person
{
public:
    Employee(std::string name, std::string company): Person{name}, company{company}
    { }
    void print() const override // явным образом указываем, что функция переопределена
    {
        Person::print();
        std::cout << "Works in " << company << std::endl;
    }
private:
    std::string company;
};

void func4(int&& x) { cout << "func5(int&&)" << endl; }

template <typename T>
void ff(T x)
{
    cout << x << endl;
}

int main()
{
    int i {5};
    const int c {0};
    int& lv {i};
    int& x = i;
    int&& y = i + 5;
    // int&& z = y;
    cout << x << " " << y << endl;

    Person tom {"Tom"};
    Person* person {&tom};
    person->print();     // Name: Tom
    Employee bob {"Bob", "Microsoft"};
    person = &bob;
    person->print();     // Name: Bob
                        // Works in Microsoft

    func4(i+1);

    ff<const int&&>(55);
    return 0;
}