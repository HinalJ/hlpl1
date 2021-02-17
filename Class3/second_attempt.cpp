#include "std_lib_facilities.h"

int main() {
	cout << "Please enter expression (we can handle +, -, *, and /)\n";
	cout << "Add an x to end expression (e.g., 2*7+1x): " << endl;

	double lval = 0, rval;
	char op;

	cin >> lval;

	try {
		while(cin >> op) {
			if (op != 'x')
				cin >> rval;
			switch (op) {
			case '+':
				lval += rval;
				break;

			case '-':
				lval -= rval;
				break;

			case '*':
				lval *= rval;
				break;

			case '/':
			{
				if (rval == 0)
					error("Division by zero!");
				lval /= rval;
			}
			default:
				cout << "Result: " << lval << endl;
				keep_window_open();
				return 0;
			}
		}
	}
	catch (exception e) {
		cout << "Exception: " << e.what() << endl;
		return 1;
	}
	catch (...) {
		cout << "Do not know which error happened!" << endl;
		return 2;
	}
}