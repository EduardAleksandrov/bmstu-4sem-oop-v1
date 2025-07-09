# include <iostream>

int main()
{
	int i = 0;
	const int ci = 0;
	int& lv = i;
	const int& clv = ci;
	int&& rv = i + 1;

	decltype(auto) x1 = i;		// int
	decltype(auto) x2 = ci;		// const int
	decltype(auto) x3 = lv;		// int&
	decltype(auto) x4 = clv;	// const int&
//	decltype(auto) x5 = rv;		// Error! lvalue -> rvalue
	decltype(auto) x6 = i + 1;	// int&&
}
