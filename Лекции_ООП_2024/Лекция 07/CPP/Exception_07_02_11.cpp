# include <iostream>

class A
{
public:
	A() {}
};

template <typename Type>
void func() noexcept(noexcept(Type())) {}

void noexceptSample()
{
	std::cout << "noexcept int(): " << noexcept(int()) << std::endl;
	std::cout << "noexcept A():   " << noexcept(A()) << std::endl << std::endl;

	std::cout << "noexcept func<int>: " << noexcept(func<int>()) << std::endl;
	std::cout << "noexcept func<A>:   " << noexcept(func<A>()) << std::endl;
}

int main()
{
    noexceptSample();
}

