# include <iostream>
# include <memory>
# include <concepts>

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
	void use(const shared_ptr<CarCreator>& creator)
	{
		shared_ptr<Car> car = creator->create();

		car->drive();
	}
}; 

int main()
{
	shared_ptr<CarCreator> creator = make_shared<ConcreteCarCreator<Sedan>>();

	User{}.use(creator);
}
