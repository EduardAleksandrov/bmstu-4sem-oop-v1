# include <iostream>
# include <memory>
# include <concepts>

using namespace std;

template <typename Derived, typename Base>
concept Derivative = is_abstract_v<Base> && is_base_of_v<Base, Derived>;

template <typename Type>
concept NotAbstract = !is_abstract_v<Type>;

template<typename Type, typename... Args>
concept Constructible = is_constructible_v<Type, Args...>;

class Car;

class CarCreator
{
public:
	template <Derivative<Car> TCar, typename... Args>
	requires NotAbstract<TCar> && Constructible<TCar, Args...>
	static unique_ptr<Car> create(Args&& ...args) 
	{
		return make_unique<TCar>(forward<Args>(args)...);
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
private:
	int seats;
	double weight;

public:
	Sedan(int s, double w) : seats(s), weight(w)
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

	template<NotAbstract TCar, typename... Args>
	void use(Args&& ...args) requires Derivative<TCar, Car>
	{
		shared_ptr<Car> car = CarCreator::create<TCar>(forward<Args>(args)...);

		car->drive();
	}
};

int main()
{
	unique_ptr<User> us = make_unique<User>();

	us->use<Sedan>(1, 100.);
}
