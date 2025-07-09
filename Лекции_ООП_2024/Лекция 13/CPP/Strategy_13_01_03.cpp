# include <iostream>
# include <memory>

using namespace std;

template <typename Type>
concept DefaultConstructible = is_default_constructible_v<Type>;

template <typename Type>
concept Algorithm = requires(Type t)
{
	t.algorithm();
};

class Strategy1
{
public:
	void algorithm() { cout << "Algorithm 1;" << endl; }
};

class Strategy2
{
public:
	void algorithm() { cout << "Algorithm 2;" << endl; }
};

template <Algorithm TStrategy = Strategy1>
requires DefaultConstructible<TStrategy>
class Context
{
private:
	unique_ptr<TStrategy> strategy{};

public:
	Context() : strategy(make_unique<TStrategy>()) {}

	void algorithmStrategy() { strategy->algorithm(); }
};

int main()
{
	using Client = Context<Strategy2>;

	shared_ptr<Client> obj = make_shared<Client>();

	obj->algorithmStrategy();
}
