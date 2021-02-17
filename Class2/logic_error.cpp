#include "std_lib_facilities.h"

int main()
{
    /* Problem with this is: when we write all only positive or only negative temps then it will be a problem.
    vector<double> temps;
    for (double temp; cin >> temp;) {
        temps.push_back(temp);
    }

    double sum = 0;
    double high_temp = 0;           //We can use lowest that it will never reach
    double low_temp = 0;            //We can assign highest that it will never reach


    for (double x : temps) {
        if (x > high_temp) high_temp = x;

        if (x < low_temp) low_temp = x;
        sum += x;
    }

    cout << "High: " << high_temp << endl;
    cout << "Low: " << low_temp << endl;
    cout << "Average: " << sum / temps.size() << endl;
    */

    
    //Improved Version
    double sum = 0;
    vector<double> temps;
    for (double temp; cin >> temp;) {
        temps.push_back(temp);
        sum += temp;
    }

    sort(temps);
    double low_temp = temps[0];
    double high_temp = temps[temps.size() - 1];

    cout << "High: " << high_temp << endl;
    cout << "Low: " << low_temp << endl;
    cout << "Average: " << sum / temps.size() << endl;

    return 0;
}