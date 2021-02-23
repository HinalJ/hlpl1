#include "std_lib_facilities.h"

const char quit = 'q';
const char print = ';';
const char number = '8';
const string prompt = "> ";
const string result = "= ";
const char let = 'L';
const char name = 'a';
const string declkey = "let";

class Token {
public:
	char kind;
	double value;
	string name;

	Token(char ch)							// make a Token from a char
		:kind(ch), value(0) { }
	Token(char ch, double val)				// make a Token from a char and a double
		:kind(ch), value(val) { }
	Token(char ch, string n) :kind(ch), name(n), value(0) {}
};

class Token_stream {
public:
	Token get(); 							// get a Token
	void putback(Token t); 					// put a Token back
	void ignore(char c);					// discard characters up to and including a c
private:
	bool full{ false }; 					// is there a Token in the buffer?
	Token buffer = { '0' }; 					// here is where we keep a Token put back using putback()
};

void Token_stream::putback(Token t) {
	if (full) error("putback() into a full buffer");
	buffer = t; 					// copy t to buffer
	full = true; 					// buffer is now full
}

Token Token_stream::get()
{
	if (full) {							// do we already have a Token ready?
		full = false;					// remove Token from buffer
		return buffer;
	}

	char ch;
	cin >> ch;

	switch (ch) {
	case print:    			// for "print"
	case quit:    				// for "quit"
	case '(': case ')': case '+': case '-': case '*': case '/': case '%': case '=':
		return Token(ch);       			// let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);         			// put digit back into the input stream
		double val;
		cin >> val;              			// now read it as a floating-point number
		return Token(number, val);
	}
	default:
		if (isalpha(ch)) {
			cin.putback(ch);
			string s;
			cin >> s;
			if (s == declkey) return Token(let); // declaration keyword
			return Token(name, s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c) { // c represents the kind of Token
// first look in buffer:
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;
	// now search input:
	char ch = 0;
	while (cin >> ch)
		if (ch == c) return;
}

class Variable {
public:
	string name;
	double value;

	Variable(string var, double val) : name(var), value(val) {}
};

vector<Variable> var_table;

double get_value(string s) {	// return the value of the Variable named s
	for (Variable v : var_table)
		if (v.name == s) return v.value;
	error("get: undefined variable ", s);
}

void set_value(string s, double d) {			// set the Variable named s to d
	for (Variable v : var_table)
		if (v.name == s) {
			v.value = d;
			return;
		}
	error("set: undefined variable ", s);
}

double term();
double primary();

Token_stream ts;

double expression() {
	double left = term();
	Token t = ts.get();

	while (true) {
		switch (t.kind) {
		case '+':
			left += term(); 				// evaluate Term and add
			t = ts.get();
			break;
		case '-':
			left -= term(); 				// evaluate Term and subtract
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left; 					// finally: no more + or –; return the answer
		}
	}
}

double term() {
	double left = primary();
	Token t = ts.get();

	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary(); 				// evaluate Term and add
			t = ts.get();
			break;
		case '/':
		{
			double d = primary(); 			// evaluate Term and subtract
			if (d == 0) {
				error("Divide by zero!");
			}
			left /= d;
			t = ts.get();
			break;
		}
		case '%':
		{
			double d = primary();
			if (d == 0) error("Divide by zero!");
			left = fmod(left, d);
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left; 					// finally: no more + or –; return the answer
		}
	}
}

double primary() {
	Token t = ts.get();
	switch (t.kind) {
	case '(':									// handle '(' expression ')'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')')
			error(" ')' expected");
		return d;
	}
	case number:
		return t.value; 						// return the number’s value
	case name:
	{
		Token next = ts.get();
		if (next.kind == '=') {	// handle name = expression
			double d = expression();
			set_value(t.name, d);
			return d;
		}
		else {
			ts.putback(next);		// not an assignment: return the value
			return get_value(t.name); // return the variable's value
		}
	}
	case '-':
		return -primary();
	case '+':
		return primary();
	default:
		error("primary expected");
	}
}

bool is_declared(string var) {		// is var already in var_table?
	for (Variable v : var_table)
		if (v.name == var) return true;
	return false;
}

double define_name(string var, double val) {		// add (var,val) to var_table
	if (is_declared(var)) error(var, " declared twice");
	var_table.push_back(Variable(var, val));
	return val;
}

double declaration()
// assume we have seen "let”
// handle: name = expression
// declare a variable called "name” with the initial value "expression”
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", var_name);
	
	double d = expression();
	define_name(var_name, d);
	return d;
}

void clean_up_mess() {
	ts.ignore(print);
}

double statement() {
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.putback(t);
		return expression();
	}
}

void calculate() {
	try {
		while (cin) {
			cout << prompt;
			Token t = ts.get();

			while (t.kind == print) t = ts.get();		//eat ';'
			if (t.kind == quit) return;
			ts.putback(t);
			cout << result << statement() << endl;

		}
	}
	catch (exception e) {
		cerr << e.what() << '\n';
		clean_up_mess();
	}
}

int main()
{
	try {
		define_name("pi", 3.14);
		calculate();
		keep_window_open();
		return 0;
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
		keep_window_open("~~");
		return 1;
	}
	catch (...) {
		cerr << "exception \n";
		keep_window_open("~~");
		return 2;
	}

	return 0;
}
