#include <iostream>
#include <vector>

using namespace std;

class Ex
{
public:
    using n = int;
};
// ----------------

class MyClass {
private:
    std::vector<int> data;

public:
    void addData(int value) {
        data.push_back(value);
    }

    // Iterator class
    class Iterator {
    private:
        std::vector<int>::iterator iter;

    public:
        Iterator(std::vector<int>::iterator it) : iter(it) {}

        int& operator*() {
            return *iter;
        }

        Iterator& operator++() {
            ++iter;
            return *this;
        }

        bool operator!=(const Iterator& other) {
            return iter != other.iter;
        }
    };

    Iterator begin() {
        return Iterator(data.begin());
    }

    Iterator end() {
        return Iterator(data.end());
    }
};
//---------------
// Forward declaration of Iterator class
template <typename T>
class Iterator;

// Container class
template <typename T>
class Container {
private:
    std::vector<T> data;

public:
    void addData(T value) {
        data.push_back(value);
    }

    friend class Iterator<T>;

    Iterator<T> begin() {
        return Iterator<T>(data.begin());
    }

    Iterator<T> end() {
        return Iterator<T>(data.end());
    }
};

// Iterator class
template <typename T>
class Iterator {
private:
    typename std::vector<T>::iterator iter;

public:
    Iterator(typename std::vector<T>::iterator it) : iter(it) {}

    T& operator*() {
        return *iter;
    }

    Iterator<T>& operator++() {
        ++iter;
        return *this;
    }

    bool operator!=(const Iterator<T>& other) {
        return iter != other.iter;
    }
};
//---------------
int main()
{
    vector<int> v{1,3,5};
    vector<int>::iterator it;
    // std::input_iterator_tag;

    for(it=v.begin(); it!=v.end(); ++it)
        cout << *it << endl;

    Ex::n t = 5;


    MyClass myClass;
    myClass.addData(1);
    myClass.addData(2);
    myClass.addData(3);

    for (MyClass::Iterator it = myClass.begin(); it != myClass.end(); ++it) {
        std::cout << *it << " ";
    }


    Container<int> myContainer;
    myContainer.addData(1);
    myContainer.addData(2);
    myContainer.addData(3);

    for (Iterator<int> it = myContainer.begin(); it != myContainer.end(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
}