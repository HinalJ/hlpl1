#include "../std_lib_facilities.h"

void skip_to_int() {
	if (cin.fail()) {
		cin.clear();
		for (char ch; cin >> ch;) {
			if (isdigit(ch) || ch == '-') {
				cin.unget();
				return;
			}
		}
	}
	error("No Input!");
}

int getInt() {
	int n = 0;
	while (true) {
		if (cin >> n)
			return n;
		cout << "Sorry, that was not a number, please try again!" << endl;
		skip_to_int();
	}
}

int getInt(int low, int high) {
	printf("Please enter an integer in this range [%d:%d]: \n", low, high);
	while (true) {
		int n = getInt();
		if (n >= low && n <= high) {
			return n;
		}
		cout << "The number you have provided is not in the range [1:10]: " << n << endl;
	}
}

int main3() {
	int n = getInt(1, 10);
	printf("Number found is: %d\n", n);

	return 0;
}