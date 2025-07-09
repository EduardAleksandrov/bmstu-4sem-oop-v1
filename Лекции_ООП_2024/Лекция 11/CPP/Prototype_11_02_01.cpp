# include <iostream>
# include <memory>

using namespace std;

class BaseObject
{
public:
	virtual ~BaseObject() = default;

	virtual unique_ptr<BaseObject> clone() = 0;
};

class Object1 : public BaseObject
{
public:
	Object1() { cout << "Calling the default constructor;" << endl; }
	Object1(const Object1& obj) { cout << "Calling the Copy constructor;" << endl; }
	~Object1() override { cout << "Calling the destructor;" << endl; }

	unique_ptr<BaseObject> clone() override
	{
		return make_unique<Object1>(*this);
	}
};

class User
{
public:
	void use(shared_ptr<BaseObject>& obj)
	{
		auto obj1 = obj->clone();
	}
};

int main()
{
	shared_ptr<BaseObject> obj = make_shared<Object1>();

	User{}.use(obj);
}
