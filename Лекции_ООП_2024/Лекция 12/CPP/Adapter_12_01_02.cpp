# include <iostream>
# include <memory>
# include <vector>

using namespace std;

class Interface
{
public:
    virtual ~Interface() = default;

    virtual void request() = 0;
};

template <typename Type>
class Adapter : public Interface
{
public:
    using PtrMethod_t = void (Type::*)();
    using CallBack_t = pair<shared_ptr<Type>, PtrMethod_t>;

    Adapter(shared_ptr<Type> object, PtrMethod_t method) : callback(object, method) {}

    void request() override { ((*callback.first).*callback.second)(); }

private:
    CallBack_t callback;
};

class AdapteeA
{
public:
    ~AdapteeA() { cout << "Destructor class AdapteeA;" << endl; }

    void specRequestA() { cout << "Method AdapteeA::specRequestA;" << endl; }
};

class AdapteeB
{
public:
    ~AdapteeB() { cout << "Destructor class AdapteeB;" << endl; }

    void specRequestB() { cout << "Method AdapteeB::specRequestB;" << endl; }
};

auto initialize()
{
    using InterPtr = shared_ptr<Interface>;

    vector<InterPtr> vec{
        make_shared<Adapter<AdapteeA>>(make_shared<AdapteeA>(), &AdapteeA::specRequestA),
        make_shared<Adapter<AdapteeB>>(make_shared<AdapteeB>(), &AdapteeB::specRequestB)
    };

    return vec;
}

int main()
{
    auto v = initialize();

    for (const auto& elem : v)
        elem->request();
}
