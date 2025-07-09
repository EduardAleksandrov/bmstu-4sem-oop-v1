# include <iostream>

using namespace std;

template <typename T, typename U>
auto sum(const T& elem1, const U& elem2) // -> decltype(elem1 + elem2)
{
	return elem1 + elem2;
}

void main()
{
	auto s = sum(1, 1.2);

	cout << "Result: " << s << endl;
}
