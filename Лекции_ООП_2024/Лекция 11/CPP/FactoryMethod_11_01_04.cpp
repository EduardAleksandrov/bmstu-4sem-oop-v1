# include <iostream>
# include <memory>

using namespace std;

template <typename Derived, typename Base>
concept Derivative = is_abstract_v<Base> && is_base_of_v<Base, Derived>;

template <typename Type>
concept NotAbstract = !is_abstract_v<Type>;

template <typename Type>
concept DefaultConstructible = is_default_constructible_v<Type>;

class Car;

template <Derivative<Car> TCar>
requires NotAbstract<TCar> && DefaultConstructible<TCar>
class CarCreator
{
public:
	unique_ptr<Car> create() const
	{
		return make_unique<TCar>();
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

# pragma endregion

class User
{
public:
    template<NotAbstract TCar>
    requires Derivative<TCar, Car>
    void use(const shared_ptr<CarCreator<TCar>>& creator)
    {
        shared_ptr<Car> car = creator->create();

        car->drive();
    }
};

int main()
{
    using SedanCreator_t = CarCreator<Sedan>;
    shared_ptr<SedanCreator_t> sedanCreator = make_shared<SedanCreator_t>();

    unique_ptr<User> user = make_unique<User>();

    user->use(sedanCreator);
}
