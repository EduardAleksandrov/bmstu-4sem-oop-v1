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

template <typename Tcrt>
class Creator
{
public:
	auto create() const
	{
		return static_cast<const Tcrt*>(this)->create_impl();
	}
};

template <Derivative<Car> TCar>
requires NotAbstract<TCar> && DefaultConstructible<TCar>
class CarCreator : public Creator<CarCreator<TCar>>
{
public:
	unique_ptr<Car> create_impl() const
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
	template<Derivative<Car> TCar>
	void use(const Creator<CarCreator<TCar>>& creator) requires NotAbstract<TCar>
	{
		auto car = creator.create();

		car->drive();
	}
};

int main()
{
	Creator<CarCreator<Sedan>> creator;

	User{}.use(creator);
}
