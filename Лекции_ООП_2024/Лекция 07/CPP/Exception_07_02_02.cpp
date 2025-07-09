# include <iostream>
# include <exception>

using namespace std;

class Exception_Alloc : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Memory allocation error!";
	}
};

class A
{
private:
	int* arr;

public:
	A(int size) : arr(new int[size] {}) {}
	~A() { delete[] arr; }
};

int main()
{
	try
	{
		try
		{
			try
			{
				A* pobj = new A(-2);

				delete pobj;
			}
			catch (const std::bad_alloc& err)
			{
				cout << err.what() << endl;

				throw Exception_Alloc();
			}
		}
		catch (const Exception_Alloc& err)
		{
			cout << err.what() << endl;

			throw;
		}
	}
	/*
	catch (const Exception_Alloc& err)
	{
		cout << err.what() << endl;
	}
	*/
	catch (...)
	{
		cout << "All errors!" << endl;
	}
}
