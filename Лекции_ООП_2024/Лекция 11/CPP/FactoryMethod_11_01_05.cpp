# include <iostream>
# include <memory>

using namespace std;


template <typename Type>
concept Abstract = is_abstract_v<Type>;

template <typename Type>
concept NotAbstract = !is_abstract_v<Type>;

template <typename Derived, typename Base>
concept Derivative = is_abstract_v<Base> && is_base_of_v<Base, Derived>;

# pragma region Variants of the concept Constructible
# define V_1

# ifdef V_1
template<typename Type, typename... Args>
concept Constructible = requires(Args... args)
{
	Type{ args... };
};

# elif defined(V_2)
template<typename Type, typename... Args>
concept Constructible = requires
{
	Type{ declval<Args>()... };
};

# elif defined(V_3)
template<typename Type, typename... Args>
concept Constructible = is_constructible_v<Type, Args...>;

# endif 

# pragma endregion

template <Abstract Tbase, typename... Args>
class BaseCreator
{
public:
	virtual ~BaseCreator() = default;

	virtual unique_ptr<Tbase> create(Args&& ...args) const = 0;
};

template <typename Tbase, Derivative<Tbase> Tprod, typename... Args>
requires NotAbstract<Tprod> && Constructible<Tprod, Args...>
class Creator : public BaseCreator<Tbase, Args...>
{
public:
	unique_ptr<Tbase> create(Args&& ...args) const override
	{
		return make_unique<Tprod>(forward<Args>(args)...);
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

class SUV : public Car
{
public:
    SUV(int seats_t, double weight_t)
    {
        cout << "Calling the SUV constructor;" << endl;
    }

    ~SUV() override
    {
        cout << "Calling the SUV destructor;" << endl;
    }

    void drive() override
    {
        cout << "Driving SUV;" << endl;
    }
};

# pragma endregion

using BaseCarCreator_t = BaseCreator<Car, int, double>;

class User
{
public:
	void use(const shared_ptr<BaseCarCreator_t>& creator)
	{
		auto car = creator->create(1, 100.);

		car->drive();
	}
};

using SedanCreator_t = Creator<Car, Sedan, int, double>;

int main()
{
    shared_ptr<BaseCarCreator_t> creator = make_shared<SedanCreator_t>();

    unique_ptr<User> user = make_unique<User>();

    user->use(creator);
}
