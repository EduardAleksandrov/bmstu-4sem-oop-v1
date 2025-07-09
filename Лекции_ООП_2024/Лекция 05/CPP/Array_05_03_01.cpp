# include <iostream>

using namespace std;

class Array
{
public:
    Array() = default;
    Array(int cnt);
    Array(const Array& ar);
    Array(Array&& ar) noexcept;
    ~Array();

    bool equals(Array ar);

    static Array minus(const Array& ar);

private:
    double* arr{ nullptr };
    int count = 0;
};

# pragma region Method
Array::Array(int cnt) : count(cnt)
{
    cout << "Array::Array(int cnt)" << endl;

    arr = new double[count];
}

Array::Array(const Array& ar) : count(ar.count)
{
    cout << "Array::Array(const Array& ar)" << endl;

    arr = new double[count];

    for (int i = 0; i < count; ++i)
        arr[i] = ar.arr[i];
}

Array::Array(Array&& ar) noexcept : count(ar.count)
{
    cout << "Array::Array(Array&& ar)" << endl;

    arr = ar.arr;
    ar.arr = nullptr;
}

Array::~Array()
{
    delete[] arr;
}

bool Array::equals(Array ar)
{
    if (count != ar.count) return false;

    int i;
    for (i = 0; i < count && arr[i] == ar.arr[i]; ++i);

    return i == count;
}

Array Array::minus(const Array& ar)
{
    Array temp(ar);

    for (int i = 0; i < temp.count; ++i)
        temp.arr[i] *= -1;

    return temp;
}

# pragma endregion

void CallsCopyConstructor(Array) {}

void DoNotCallsCopyConstructor(Array&) {}

int main()
{
    Array ar{ 5 };

    cout << endl;
    cout << (ar.equals(Array::minus(ar)) ? "true" : "false") << endl;
    cout << endl;

    CallsCopyConstructor(ar);
    DoNotCallsCopyConstructor(ar);
    Array ar1(move(ar));
}

