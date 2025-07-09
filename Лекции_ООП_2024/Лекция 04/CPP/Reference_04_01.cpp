#include <iostream>

using namespace std;

void lValues()
{
    int i = 0;

    int& lref1 = i;
    int& lref2(i);
    int& lref3{ i };
    int& lref4 = { i };

    lref1 += 1;
    cout << "lvalues: " << i << " " << lref1 << " " << lref2 << " " << lref3 << " " << lref4;

    // int& lv2 = 2;        // Error!	(не lvalue)
    // int& lv3 = i + 1;    // Error!	(не lvalue)
    const int& lv4 = 2 + 1; // Ok!		(создается объект)

    cout << " " << lv4 << endl;
}

void rValues()
{
    int i = 0;

    // int&& rv1 = i;        // Error!	(не rvalue)
    int&& rv2 = 2;           // Ok!
    int&& rv3 = i + 1;       // Ok!
    const int&& rv4 = i + 1; // Ok!
    ++rv2;                   // Ok!
    cout << "rvalues: " << rv2 << " " << rv3 << " " << rv4 << endl;

    // int &&rv5 = rv2; // Error!	(не rvalue)
    int& lv5 = rv2;  // Ok!
    lv5++;
    cout << "lv5 and rv2: " << lv5 << " " << rv2 << endl;

    int&& rv6 = (int)i;       // Ok!	( int(i) )
    int&& rv7 = std::move(i); // Ok!
    cout << "rv6 and rv7: " << rv6 << " " << rv7 << endl;
}

int main()
{
    lValues();
    rValues();
}
