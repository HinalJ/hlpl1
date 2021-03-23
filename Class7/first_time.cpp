#include "../std_lib_facilities.h"

struct Reading{
    int hour;
    double temperature;

    Reading(int h, double t) : hour(h), temperature(t){}
};

int main0()
{
    String iname;
    String oname;

    try {
        cout << "Please input file name to read data from!" << endl;

        cin >> iname;
        ifstream ifs{ iname };
        if (!ifs) {
            error("File not found!");
        }

        cout << "Please input file name to output data to!" << endl;
        cin >> oname;
        ofstream ofs{ oname };
        if (!ofs) {
            error("File not opened properly!");
        }

        vector<Reading> temps;
        int hour;
        double temperature;

        while (ifs >> hour >> temperature) {
            if (hour < 0 || hour > 23)
                error("Hour input is not valid");
            temps.push_back(Reading(hour, temperature));
        }

        for (Reading& value : temps) {
            ofs << "(" << value.hour << ", " << value.temperature << ")" << endl;;
        }
        cout << "Success!" << endl;
        return 0;
    }
    catch (exception& e) {
        cout << e.what() << endl;
        return 1;
    }
}

