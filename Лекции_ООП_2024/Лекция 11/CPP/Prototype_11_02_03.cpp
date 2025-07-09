# include <iostream>
# include <memory>
# include <concepts>

using namespace std;

class Base
{
public:
    virtual ~Base() = default;

    virtual unique_ptr<Base> clone() const = 0;
    virtual ostream& print(ostream& os) const = 0;
};

template <typename Type>
concept Abstract = is_abstract_v<Type>;

template <Abstract Base, typename Derived>
class Cloner : public Base
{
public:
    unique_ptr<Base> clone() const override
    {
        return make_unique<Derived>(static_cast<const Derived&>(*this));
    }
};

class Descendant : public Cloner<Base, Descendant>
{
private:
    int data;

public:
    Descendant(int d) : data(d) { cout << "Calling the constructor;" << endl; }
    Descendant(const Descendant& obj) : data(obj.data)
    {
        cout << "Calling the Copy constructor;" << endl;
    }
    ~Descendant() override { cout << "Calling the destructor;" << endl; }

    ostream& print(ostream& os) const override
    {
        return os << "data = " << data;

    }
};

// C++23
/*
template <typename Base>
struct Cloner : public Base
{
    template <typename Self>
    unique_ptr<Base> clone(this Selt&& self) const override
    {
        return unique_ptr<Base>(new Self(self));
    }
};

class Descendant : public Cloner<Base>
{
private:
    int data;

public:
    Descendant(int d) : data(d) {}

    ostream& print(ostream& os) const override
    {
        return os << "data = " << data;

    }
};
*/

ostream& operator <<(ostream& os, const unique_ptr<Base>& obj)
{
    return obj->print(os);
}

class User
{
public:
    void use(unique_ptr<Base>& obj)
    {
        auto tmp = obj->clone();

        cout << tmp << endl;
    }
};

int main()
{
    unique_ptr<Base> v1 = make_unique<Descendant>(10);

    User{}.use(v1);
}
