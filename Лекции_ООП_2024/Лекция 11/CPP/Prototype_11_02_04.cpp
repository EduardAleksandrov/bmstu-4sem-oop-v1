# include <iostream>
# include <memory>
# include <concepts>

using namespace std;

class Base
{
public:
    virtual ~Base() = default;

    virtual unique_ptr<Base> clone() const;
    virtual ostream& print(ostream& os) const = 0;
};

class ClonerBase
{
public:
    virtual unique_ptr<Base> clone() const = 0;
};

template <typename Derived>
class Cloner : public ClonerBase
{
public:
    unique_ptr<Base> clone() const override
    {
        return make_unique<Derived>(static_cast<const Derived&>(*this));
    }
};

class Descendant : public Base, public Cloner<Descendant>
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

unique_ptr<Base> Base::clone() const
{
    return dynamic_cast<const ClonerBase*>(this)->clone();
}

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
    unique_ptr<Base> v = make_unique<Descendant>(10);

    User{}.use(v);
}
