#include "std_lib_facilities.h"
#include "date_interface.h"

namespace date {

	// member function definitions:

	Date::Date(int yy, Month mm, int dd) : y(yy), m(mm), d(dd){
		if (!is_date(yy, mm, dd)) throw Invalid();
	}

	const Date& default_date(){
		static const Date dd(2001, Date::jan, 1); // start of 21st century
		return dd;
	}

	Date::Date()
		:y(default_date().year()), m(default_date().month()), d(default_date().day()){}

	void Date::add_day(int n){
		// Not Implemented - Try-This
	}

	void Date::add_month(int n) {
		// Not Implemented - Try-This
	}

	void Date::add_year(int n){
		if (m == feb && d == 29 && !leapyear(y + n)) 
		{								// beware of leap years!
										// makes sense for both positive and negative n (n==0 should be impossible here)
			m = mar;					// use March 1 instead of February 29
			d = 1;
		}
		y += n;
	}

	int days_in_month(int y, Date::Month m){
		switch (m) {
		case Date::feb:                        // the length of February varies
			return (leapyear(y)) ? 29 : 28;
		case Date::apr: case Date::jun: case Date::sep: case Date::nov:
			return 30;
		default:
			return 31;
		}
	}

	bool is_date(int y, Date::Month  m, int d){
		// assume that y is valid

		if (d <= 0) return false;            // d must be positive
		if (days_in_month(y, m) < d) return false;

		return true;
	}

	bool leapyear(int y){
		// Not Implemented - Try-This
		return false;				//default value
	}

	bool operator==(const Date& a, const Date& b) {
		return a.year() == b.year() && a.month() == b.month() && a.day() == b.day(); 
	}


	bool operator!=(const Date& a, const Date& b){ 
		return !(a == b);
	}


	ostream& operator<<(ostream& os, const Date& d){
		return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
	}

	Date operator+(const Date& d, int dd)  // dd days beyond d
	{
		Date x = d;
		x.add_day(dd);
		return x;
	}

} 

using namespace date;

int main() {
	try
	{
		Date dd = Date(2020, Date::dec, 25);
		cout << dd;
	}
	catch (date::Date::Invalid&) {
		cerr << "error: Invalid date\n";
		keep_window_open("~");	
	}
	catch (runtime_error& e) {	
		cout << e.what() << '\n';
		keep_window_open("~");	
	}
}
