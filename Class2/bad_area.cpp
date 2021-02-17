#include "std_lib_facilities.h"

class Bad_area {};

int area(int length, int width) {
    if (length <= 0 || width <= 0) throw Bad_area{};
    return length * width;
}

int main()
{
    try {
        int i, j;
        cin >> i >> j;
        cout << area(i, j) << endl;
    }
    catch (Bad_area) {
        cout << "Bad arguments" << endl;
    }

    return 0;
}