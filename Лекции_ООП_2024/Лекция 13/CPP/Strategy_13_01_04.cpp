# include <iostream>
# include <memory>

using namespace std;

template <typename Derived, typename Base>
concept Derivative = is_abstract_v<Base> && is_base_of_v<Base, Derived>;

template <typename Type>
concept NotAbstract = !is_abstract_v<Type>;

template <typename Type>
concept DefaultConstructible = is_default_constructible_v<Type>;

template <typename Type>
concept Algorithm = requires(Type t)
{
	t.algorithm();
};

class Strategy
{
public:
	virtual ~Strategy() = default;

	virtual void algorithm() = 0;
};

class ConStrategy1 : public Strategy
{
public:
	void algorithm() override { cout << "Algorithm 1;" << endl; }
};

class ConStrategy2 : public Strategy
{
public:
	void algorithm() override { cout << "Algorithm 2;" << endl; }
};

template <typename T>
struct Type2Type
{
	using type = T;
};

class Context
{
private:
	unique_ptr<Strategy> strategy{};

public:
	template <Derivative<Strategy> TStrategy = ConStrategy1>
	requires NotAbstract<TStrategy> && Algorithm<TStrategy> && DefaultConstructible<TStrategy>
	Context(Type2Type<TStrategy>) : strategy(make_unique<TStrategy>()) {}

	void algorithmStrategy() { strategy->algorithm(); }
};

int main()
{
	shared_ptr<Context> obj = make_shared<Context>(Type2Type<ConStrategy2>());

	obj->algorithmStrategy();
}
