# include <iostream>
# include <memory>
# include <exception>

using namespace std;

class BaseObject
{
public:
	virtual ~BaseObject() = default;

	unique_ptr<BaseObject> clone();

private:
	virtual unique_ptr<BaseObject> doClone() = 0;
};

class Object1 : public BaseObject
{
public:
	Object1() { cout << "Calling the default constructor;" << endl; }
	Object1(const Object1& obj) { cout << "Calling the Copy constructor;" << endl; }
	~Object1() override { cout << "Calling the destructor;" << endl; }

private:
	unique_ptr<BaseObject> doClone() override
	{
		return make_unique<Object1>(*this);
	}
};

class Object11 : public Object1 { };

unique_ptr<BaseObject> BaseObject::clone()
{
	unique_ptr<BaseObject> objclone = doClone();

	if (typeid(*objclone) != typeid(*this)) throw runtime_error("Error clone!");

	return objclone;
}

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
	try
	{
		shared_ptr<BaseObject> obj = make_shared<Object11>();

		User{}.use(obj);
	}
	catch (exception& err)
	{
		cout << err.what() << endl;
	}

}
