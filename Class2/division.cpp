#include "std_lib_facilities.h"

int main() 
{
    try 
    {
        cin >> i >> j;
        if (j == 0) throw runtime_error("Division by zero not possible!");
        cout << i / j << endl;
    }
    catch (runtime_error e) {
        cout << "Runtime: " << e.what() << endl;
    }


    return 0;
}