# include <iostream>
# include <initializer_list>
# include <memory>
# include <map>
# include <exception>

using namespace std;

template <typename Derived, typename Base>
concept Derivative = is_abstract_v<Base> && is_base_of_v<Base, Derived>;

template <typename Type>
concept NotAbstract = !is_abstract_v<Type>;

template <typename Type>
concept DefaultConstructible = is_default_constructible_v<Type>;

class Car;

class CarCreator
{
public:
    virtual ~CarCreator() = default;
    virtual unique_ptr<Car> create() const = 0;
};

template <Derivative<Car> TCar>
requires NotAbstract<TCar> && DefaultConstructible<TCar>
class ConcreteCarCreator : public CarCreator
{
public:
    unique_ptr<Car> create() const override
    {
        return make_unique<TCar>();
    }
};

class CarCreatorMaker
{
public:
    template <Derivative<Car> TCar>
    static unique_ptr<CarCreator> createCarCreator() requires NotAbstract<TCar>
    {
        return make_unique<ConcreteCarCreator<TCar>>();
    }
};

# pragma region Car
class Car
{
public:
    virtual ~Car() = default;
    virtual void drive() = 0;
};

class Sedan : public Car
{
public:
    Sedan()
    {
        cout << "Sedan constructor called" << endl;
    }

    ~Sedan() override
    {
        cout << "Sedan destructor called" << endl;
    }

    void drive() override
    {
        cout << "Driving sedan" << endl;
    }
};

class SUV : public Car
{
public:
    SUV()
    {
        cout << "Calling the SUV constructor" << endl;
    }

    ~SUV() override
    {
        cout << "Calling the SUV destructor" << endl;
    }

    void drive() override
    {
        cout << "Driving SUV" << endl;
    }
};

# pragma endregion

class VehicleSolution
{
public:
    using CreateCreator = unique_ptr<CarCreator>(&)();
    using CallBackMap = map<size_t, CreateCreator>;

public:
    VehicleSolution() = default;
    VehicleSolution(initializer_list<pair<size_t, CreateCreator>> list);

    bool registrate(size_t id, CreateCreator createfun);
    bool check(size_t id)
    {
        return callbacks.erase(id) == 1;
    }

    unique_ptr<CarCreator> create(size_t id);

private:
    CallBackMap callbacks;
};

# pragma region Solution Methods
VehicleSolution::VehicleSolution(initializer_list<pair<size_t, CreateCreator>> list)
{
    for (auto&& elem : list)
        this->registrate(elem.first, elem.second);
}

bool VehicleSolution::registrate(size_t id, CreateCreator createfun)
{
    return callbacks.insert(CallBackMap::value_type(id, createfun)).second;
}

unique_ptr<CarCreator> VehicleSolution::create(size_t id)
{
    CallBackMap::const_iterator it = callbacks.find(id);

    return it != callbacks.end() ? unique_ptr<CarCreator>(it->second()) : nullptr;
}

# pragma endregion

shared_ptr<VehicleSolution> make_solution(
    initializer_list<pair<size_t, VehicleSolution::CreateCreator>> list)
{
    return shared_ptr<VehicleSolution>(new VehicleSolution(list));
}

class User
{
public:
    void use(const shared_ptr<CarCreator>& creator)
    {
        if (!creator) throw runtime_error("The creator is missing!");

        shared_ptr<Car> car = creator->create();
        car->drive();
    }
};

int main()
{
    try
    {
        shared_ptr<VehicleSolution> solution
            = make_solution({ {1, CarCreatorMaker::createCarCreator<Sedan>} });

        if (!solution->registrate(2, CarCreatorMaker::createCarCreator<SUV>))
        {
            throw runtime_error("Error registration!");
        }
        shared_ptr<CarCreator> cr(solution->create(2));

        User{}.use(cr);
    }
    catch (runtime_error& err)
    {
        cout << err.what() << endl;
    }
}
