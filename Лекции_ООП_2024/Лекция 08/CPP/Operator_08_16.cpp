# include <iostream>
# include <assert.h>

using namespace std;

unsigned long long operator "" _b(const char* str)
{
    size_t size = strlen(str);

    unsigned long long result = 0;
    for (size_t i = 0; i < size; ++i)
    {
        assert(str[i] == '1' || str[i] == '0');
        (result <<= 1) |= str[i] - '0';
    }

    return result;
}

class Weight
{
    double w;

public:
    explicit Weight(double wt) : w(wt) {}

    explicit operator double() const { return w; }
};

Weight operator "" _kg(long double val)
{
    return Weight(val);
}

ostream& operator <<(ostream& os, const Weight& weight)
{
    return os << double(weight);
}

int main()
{
    cout << 101100_b << endl;
    cout << 76.3_kg << endl;
}
