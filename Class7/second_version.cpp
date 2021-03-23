#include "../std_lib_facilities.h"

int main2() {
	cout << "Please enter an integer in this range [1:10]" << endl;

	int n = 0;

	while (true) {
		try {
			cin >> n;
			if (cin) {												// Whether it is an integer of not
				if (n >= 1 && n <= 10) { 
					cout << n << ", " << "Success!" << endl;
					break; 
				}
				cout << n << ", Integer is not in range [1:10]" << endl;
			}
			else if (cin.fail()) {									// When we enetered apart from numbers
				cin.clear();
				cout << "Sorry, that was not a number; please try again\n";
				for (char ch; cin >> ch && !isdigit(ch););			// Throw away non-digits and find if there is a digit

				if (!cin)
					error("No Input!");
				cin.unget();										// Puts the digit back in stream
			}
			else {
				error("no input!");
			}
			
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
		
	}
	

	return 0;
}