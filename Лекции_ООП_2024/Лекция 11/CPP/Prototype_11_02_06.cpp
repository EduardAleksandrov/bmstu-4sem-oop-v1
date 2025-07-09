# include <iostream>
# include <memory>

// использованные идеомы: CRTP, NVI

using namespace std;

struct NullType { };

template<typename Derived, typename Base = NullType>
struct Cloner : public Base
{
    virtual ~Cloner() = default;

    unique_ptr<Derived> clone() const
    {
        return unique_ptr<Derived>(static_cast<Derived*>(this->doClone()));
    }

protected:
    virtual Cloner* doClone() const
    {
        return new Derived(*static_cast<const Derived*>(this));
    }
};

class Car : public Cloner<Car>
{
public:
    Car() { cout << "Calling the car default constructor;" << endl; }
    Car(const Car& car) { cout << "Calling the car Copy constructor;" << endl; }

    ~Car() override { cout << "Calling the car destructor;" << endl; }

    virtual ostream& print(ostream& os) const
    {
        return os << "Car";

    }
};

class Sedan : public Cloner<Sedan, Car>
{
public:
    Sedan() { cout << "Calling the sedan default constructor;" << endl; }
    Sedan(const Sedan& car) { cout << "Calling the sedan Copy constructor;" << endl; }

    ~Sedan() override { cout << "Calling the sedan destructor;" << endl; }

    ostream& print(ostream& os) const override
    {
        return os << "Sedan";
    }
};

ostream& operator <<(ostream& os, const unique_ptr<Car>& vehicle)
{
    return vehicle->print(os);
}

class User
{
public:
    void use(unique_ptr<Car>& vehicle)
    {
        auto newVehicle = vehicle->clone();

        cout << newVehicle << endl;
    }
};

int main()
{
    unique_ptr<Car> vehicle = make_unique<Sedan>();

    User{}.use(vehicle);
}
