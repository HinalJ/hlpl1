#include "std_lib_facilities.h"

// As out_of_range and runtime are both exceptions so we can catch them together
int main()
{
    try {

        cin >> i >> j;
        if (j == 0)
            throw runtime_error("Division by zero!");

        vector<int> v;
        v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        for (int i = 0; i <= v.size(); i++)             // throw out_of_range error
            cout << v[i] << endl;
    }
    catch (exception e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}