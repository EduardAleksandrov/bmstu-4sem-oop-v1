# include <iostream>

using namespace std;

int func(int& p) { return 1; }
int func(int&& p) { return 2; }
int func(const int& p) { return 3; }
int func(const int&& p) { return 4; }

int main()
{
	int i = 1;
	const int j = 1;

	cout << func(i) << endl;
	cout << func(1) << endl;
	cout << func(j) << endl;
	cout << func(move(j)) << endl;
}
