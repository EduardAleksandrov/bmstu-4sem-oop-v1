# include <iostream>

using namespace std;

template <typename T>
T f(T&& x) { return x; }

auto&& g(auto&& x) { return x; }

auto&& h(auto&& x) { return forward<decltype(x)>(x); }

int main()
{
	int a;
	const int b = 0;
	int&& c = 0;

// int& f<int&>(int&)
	f(a); f(c);
	g(a); g(c);
	h(a); h(c);

// const int& f<const int&>(const int&)
	f(b);	
	g(b);
	h(b);

// int f<int>(int&&)
	f(0);

// int& f<int>(int&&)
	g(0);

// int&& h<int>(int&&)
	h(0);
}
