#include "std_lib_facilities.h"

int main() 
{
    try 
    {
        int i = narrow_cast<int>(10);
    }
    catch (runtime_error e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}