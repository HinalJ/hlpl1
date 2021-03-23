#include "../std_lib_facilities.h"

const double not_a_reading = -7777;
const int not_a_month = -1;

struct Day{
	vector<double> hour{ vector<double>(24, not_a_reading) };
};

struct Month{
	int month{ not_a_month };
	vector<Day> day{ 32 };
};

struct Year{
	int year;
	vector<Month> month{ 12 };
};

struct Reading{
	int day;
	int hour;
	double temperature;
};

istream& operator >> (istream& is, Reading& r);
istream& operator >> (istream& is, Month& m);
istream& operator >> (istream& is, Year& y);
string int_to_month(int i);
int month_to_int(const string& s);
bool is_valid(const Reading& r);
void end_of_loop(istream& is, char term, const string& message);
void print_year(ofstream& ofs, const Year& y);

int main(){
	try{
		cout << "Please enter input file name\n";
		string iname;
		cin >> iname;
		ifstream ist{ iname };
		if (!ist)
			error("can't open input file ", iname);

		ist.exceptions(ist.exceptions() | ios_base::badbit);

		cout << "Please enter output file name\n";
		string oname;
		cin >> oname;
		ofstream ost{ oname };
		if (!ost)
			error("can't open output file ", oname);
		
		vector<Year> ys;
		while (true){
			Year y;
			if (!(ist >> y))
				break;
			
			ys.push_back(y);
		}
		cout << "read " << ys.size() << " years of readings\n";

		for (const Year& y : ys)
			print_year(ost, y);
		
	}
	catch (const runtime_error& e){
		cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch (const exception& e){
		cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 2;
	}
	keep_window_open();
	return 0;
}

istream& operator>>(istream& is, Reading& r){
	char ch1;
	if (is >> ch1 && ch1 != '('){
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}
	char ch2;
	int d;
	int h;
	double t;
	is >> d >> h >> t >> ch2;
	if (!is || ch2 != ')')
		error("bad reading");
	
	r.day = d;
	r.hour = h;
	r.temperature = t;
	return is;
}

istream& operator>>(istream& is, Month& m){
	char ch = 0;
	if (is >> ch && ch != '{')
	{
		is.unget();

		is.clear(ios_base::failbit);
		return is;
	}

	string month_marker;
	string mm;
	is >> month_marker >> mm;
	if (!is || month_marker != "month")
		error("bad start of month");
	
	m.month = month_to_int(mm);

	int duplicates = 0;
	int invalids = 0;
	for (Reading r; is >> r;){
		if (is_valid(r)){
			if (m.day[r.day].hour[r.hour] != not_a_reading)
				++duplicates;
			m.day[r.day].hour[r.hour] = r.temperature;
		}
		else
			++invalids;
	}
	if (invalids)
		error("invalid readings in month", invalids);
	
	if (duplicates)
		error("duplicate readings in month", duplicates);
	
	end_of_loop(is, '}', "bad end of month");
	return is;
}

istream& operator>>(istream& is, Year& y){
	char ch;
	is >> ch;
	if (ch != '{')
	{
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	string year_marker;
	int yy;
	is >> year_marker >> yy;
	if (!is || year_marker != "year")
		error("bad start of year");
	
	y.year = yy;

	while (true)
	{
		Month m;
		if (!(is >> m))
			break;
		
		y.month[m.month] = m;
		
	}

	end_of_loop(is, '}', "bad end of year");
	return is;
}

int month_to_int(const string& s){
	vector<string> month_input_tbl = { "jan", "feb", "mar", "apr", "may", "jun", 
		"jul", "aug", "sep", "oct", "nov", "dec" };

	for (int i = 0; i < 12; ++i)
		if (month_input_tbl[i] == s)
			return i;
		
	return -1;
}

string int_to_month(int i){
	vector<string> month_print_tbl = { "January", "February", "March", "April", "May", "June", 
		"July", "August", "September", "October", "November", "December" };

	if (i < 0 || i >= 12)
		error("bad month index");
	
	return month_print_tbl[i];
}

bool is_valid(const Reading& r){
	constexpr double implausible_min = -200;
	constexpr double implausible_max = 200;

	if (r.day < 1 || r.day > 31)
		return false;
	
	if (r.hour < 0 || r.hour > 23)
		return false;
	
	if (r.temperature < implausible_min || r.temperature > implausible_max)
		return false;
	
	return true;
}

void end_of_loop(istream& ist, char term, const string& message){
	if (ist.fail())
	{
		ist.clear();
		char ch;
		if (ist >> ch && ch == term) return;
		
		error(message);
	}
}

void print_year(ofstream& ofs, const Year& y){
	for (int k = 0; k < y.month.size(); ++k)
		for (int i = 1; i < 32; i++) {
			for (int j = 0; j < 24; j++) {
				if (y.month[k].day[i].hour[j] != -7777)
					ofs << "Year: " << y.year << "\tMonth: " << int_to_month(k) 
					<< "    Hour: " << j << "    Temp: " << y.month[k].day[i].hour[j] << endl;
			}
		}
}