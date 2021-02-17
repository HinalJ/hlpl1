#include "std_lib_facilities.h"

class Token {
public:
	char kind;
	double value;

	Token(char ch)    // make a Token from a char
		:kind(ch), value(0) { }
	Token(char ch, double val)     // make a Token from a char and a double
		:kind(ch), value(val) { }
};

class Token_stream {
public:
	Token get(); 			// get a Token (get() is defined in §6.8.2)
	void putback(Token t); 		// put a Token back
private:
	bool full{ false }; 		// is there a Token in the buffer?
	Token buffer = {'0'}; 			// here is where we keep a Token put back using putback()
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
	case ';':    			// for "print"
	case 'q':    			// for "quit"
	case '(': case ')': case '+': case '-': case '*': case '/':
		return Token{ ch };       			// let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);         			// put digit back into the input stream
		double val;
		cin >> val;              			// now read it as a floating-point number
		return Token{ '8', val };   			// let '8' represent "a number"
	}
	default:
		error("Bad token");
	}
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
			return left; 				// finally: no more + or –; return the answer
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
				double d = primary(); 				// evaluate Term and subtract
				if (d == 0) {
					error("Divide by zero!");
				}
				left /= d;
				t = ts.get();
				break;
			}
			default:
				ts.putback(t);
				return left; 				// finally: no more + or –; return the answer
		}
	}
}

double primary() {
	Token t = ts.get();
	switch (t.kind) {
	case '(':								// handle '(' expression ')'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')')
			error(" ')' expected");
		return d;
	}
	case '8': 							// we use '8' to represent a number
		return t.value; 				// return the number’s value
	default:
		cout << t.kind;
		error("primary expected");
	}

}

int main()
{	
	try {
		double val = 0;
		
		while (cin) {
			Token t = ts.get();

			if (t.kind == 'q') break;
			if (t.kind == ';')
				cout << "= " << val << '\n';
			else
				ts.putback(t);
			val = expression();
		}
		keep_window_open();
		return 0;
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch (...) {
		cerr << "exception \n";
		keep_window_open();
		return 2;
	}
}
