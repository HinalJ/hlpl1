#include "std_lib_facilities.h"

class Token {
public:
	char kind;
	double value;

Token(char ch)							// make a Token from a char
	:kind(ch), value(0) { }
Token(char ch, double val)				// make a Token from a char and a double
	:kind(ch), value(val) { }
};



/* So to match grammar rules we need to implement following:
*	get_token();
*	expression();
*	term();
*	primary();
*/

Token get_token() {
	char ch;
	cin >> ch;

	switch (ch) {
		//not yet   case ';':    			// for "print"
		//not yet   case 'q':    			// for "quit"
	case '(': case ')': case '+': case '-': case '*': case '/':
		return Token(ch);       			// let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);         			// put digit back into the input stream
		double val;
		cin >> val;              			// now read it as a floating-point number
		return Token('8', val);   			// let '8' represent "a number"
	}
	default:
		error("Bad token");
	}
}


double expression();
double term();

double expression() {
	double left = expression();
	Token t = get_token();

	switch (t.kind) {
	case '+':
		return left + term();
	case '-':
		return left - term();
	default:
		return left;
	}
}

// What is problem with expression() ? It is inifinite loop as in first line of expression it calls itself always.

int main() {
	cout << "Implementing Expressions!\n";

	return 0;
	
}