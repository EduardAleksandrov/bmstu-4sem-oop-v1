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

class CarCreator
{
public:
	virtual ~CarCreator() = default;

	shared_ptr<Car> getCar();

protected:
	virtual shared_ptr<Car> create() = 0;

private:
	shared_ptr<Car> car{ nullptr };
};

template <Derivative<Car> TCar>
requires NotAbstract<TCar> && DefaultConstructible<TCar>
class ConcreteCarCreator : public CarCreator
{
protected:
	shared_ptr<Car> create() override
	{
		return make_shared<TCar>();
	}
};

# pragma region Creator Method 
shared_ptr<Car> CarCreator::getCar()
{
	if (!car)
	{
		car = create();
	}

	return car;
}

# pragma endregion

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
		shared_ptr<Car> car1 = creator->getCar();
		shared_ptr<Car> car2 = creator->getCar();

		cout << "use count = " << car1.use_count() << endl;
		car1->drive();
	}
}; 

int main()
{
	shared_ptr<CarCreator> creator = make_shared<ConcreteCarCreator<Sedan>>();

	unique_ptr<User> user = make_unique<User>();
	user->use(creator);
}
