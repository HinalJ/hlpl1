#include "std_lib_facilities.h"

int main() {
	double lval = 0, rval, result = 0;
	char op;

	cin >> lval >> op >> rval;

	try {
		if (op == '+') {
			result = lval + rval;
		}
		else if (op == '-') {
			result = lval - rval;
		}
		else if (op == '*') {
			result = lval * rval;
		}
		else if (op == '/') {
			if (rval == 0)
				error("Division by zero!");
			result = lval / rval;
		}

		cout << "Result: " << result << endl;
		return 0;
	}
	catch (exception e) {
		cout << "Exception: " << e.what() << endl;
		return 1;
	}
}