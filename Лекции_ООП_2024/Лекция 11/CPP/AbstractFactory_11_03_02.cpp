# include <iostream>
# include <memory>

using namespace std;

# pragma region Type List
class NullType {};

template <typename... Types>
struct TypeList;

template <>
struct TypeList<> {};

template <typename H>
struct TypeList<H>
{
	using Head = H;
	using Tail = NullType;
};

template <typename H, typename... Types>
struct TypeList<H, Types...>
{
	using Head = H;
	using Tail = TypeList<Types...>;
};

#pragma endregion

# pragma region Reverse List
template <typename TList, typename Type> struct Append;

template <typename Type>
struct Append<TypeList<>, Type>
{
	using Result = TypeList<Type>;
};

template <typename Head, typename Type>
struct Append<TypeList<Head>, Type>
{
	using Result = TypeList<Head, Type>;
};

template <typename Head, typename... Tail, typename Type>
struct Append<TypeList<Head, Tail...>, Type>
{
	using Result = TypeList<Head, Tail..., Type>;
};

template <typename TList> struct Reverse;

template <typename Type>
struct Reverse<TypeList<Type>>
{
	using Result = TypeList<Type>;
};

template <typename Head, typename Tail>
struct Reverse<TypeList<Head, Tail>>
{
	using Result = Append<TypeList<Tail>, Head>::Result;
};

template <typename Head, typename... Tail>
struct Reverse<TypeList<Head, Tail...>>
{
	using Result = Append<typename Reverse<TypeList<Tail...>>::Result, Head>::Result;
};

# pragma endregion

# pragma region Scatter Hierarchy
template <typename TList, template <typename> typename Unit>
class ScatterHierarchy;

template <template <typename> typename Unit>
class ScatterHierarchy<TypeList<>, Unit> {};

template <template <typename> typename Unit, typename AtomicType>
class ScatterHierarchy<TypeList<AtomicType>, Unit> : public Unit<AtomicType>
{
public:
	using LeftBase = Unit<AtomicType>;
};

template <template <typename> typename Unit, typename Head, typename... Tail>
class ScatterHierarchy<TypeList<Head, Tail...>, Unit>
	: public ScatterHierarchy<TypeList<Head>, Unit>, public ScatterHierarchy<TypeList<Tail...>, Unit>
{
public:
	using TList = TypeList<Head, Tail...>;
	using LeftBase = ScatterHierarchy<TypeList<Head>, Unit>;
	using RightBase = ScatterHierarchy<TypeList<Tail...>, Unit>;
};

# pragma endregion

# pragma region Linear Hierarchy
struct EmptyType {};

template
<
	typename TList,
	template <typename AtomicType, typename Base> typename Unit,
	typename Root = EmptyType 
>
class LinearHierarchy;

template
<
	typename Root,
	template <typename, typename> typename Unit,
	typename Head, typename... Tail
>
class LinearHierarchy<TypeList<Head, Tail...>, Unit, Root>
	: public Unit< Head, LinearHierarchy<TypeList<Tail...>, Unit, Root> >
{};

template
<
	typename Root,
	template <typename, typename> typename Unit,
	typename Head
>
class LinearHierarchy<TypeList<Head>, Unit, Root>
	: public Unit<Head, Root>
{};

# pragma endregion

template <typename Type>
concept Abstract = is_abstract_v<Type>;

template <typename Type>
concept NotAbstract = !is_abstract_v<Type>;

template < typename T>
class Type2Type
{
public:
	using type = T;
};

template <Abstract Tbase>
class BaseCreator
{
public:
	virtual ~BaseCreator() = default;

	virtual unique_ptr<Tbase> create(Type2Type<Tbase>) = 0;
};

template <template <Abstract> typename Unit, Abstract... Types>
class AbstractFactory : public ScatterHierarchy<TypeList<Types...>, Unit>
{
public:
	using ProductList = TypeList<Types...>;
	template <typename Type>
	unique_ptr<Type> create()
	{
		BaseCreator<Type>& unit = *this;
		return unit.create(Type2Type<Type>());
	}
};

template <NotAbstract ConcreteProduct, typename Base>
//requires is_base_of_v<typename Base::ProductList::Head, ConcreteProduct>
class Creator : public Base
{
private:
	using BaseProductList = typename Base::ProductList;

protected:
	using ProductList = typename BaseProductList::Tail;

public:
	using AbstractProduct = typename BaseProductList::Head;

	unique_ptr<AbstractProduct> create(Type2Type<AbstractProduct>) override
	{
		return make_unique<ConcreteProduct>();
	}
};

template
<
	typename AbstractFact,
	template <typename, typename> typename Creator,
	NotAbstract... Types
>
class ConcreteFactory
	: public LinearHierarchy<typename Reverse<TypeList<Types...>>::Result, Creator, AbstractFact>
{
	using AbstractProductList = typename AbstractFact::ProductList;
	using ConcreteProductList = TypeList<Types...>;
};

class Image {};
class Color {};

class BaseGraphics
{
public:	virtual ~BaseGraphics() = 0;
};
BaseGraphics::~BaseGraphics() {}

class BasePen
{
public:	virtual ~BasePen() = 0;
};
BasePen::~BasePen() {}

class BaseBrush
{
public:	virtual ~BaseBrush() = 0;
};
BaseBrush::~BaseBrush() {}

class QtGraphics : public BaseGraphics
{
public:
	QtGraphics() { cout << "Calling the QtGraphics constructor;" << endl; }
	~QtGraphics() override { cout << "Calling the QtGraphics destructor;" << endl; }
};

class QtPen : public BasePen {};
class QtBrush : public BaseBrush {};

using AbstractGrFactory = AbstractFactory<BaseCreator, BaseGraphics, BasePen, BaseBrush>;
using QtGrFactory = ConcreteFactory<AbstractGrFactory, Creator, QtGraphics, QtPen, QtBrush>;

class User
{
public:
	void use(shared_ptr<AbstractGrFactory>& cr)
	{
		auto ptr = cr->create<BaseGraphics>();
	}
};

int main()
{
	shared_ptr<AbstractGrFactory> gr = make_shared<QtGrFactory>();

	unique_ptr<User> us = make_unique<User>();

	us->use(gr);
}
