#include "../std_lib_facilities.h"

void sizes(char ch, int i, int* p) {
	cout << "the size of char is " << sizeof(char) << ' ' << sizeof(ch) << '\n';
	cout << "the size of int is " << sizeof(int) << ' ' << sizeof(i) << '\n';
	cout << "the size of int* is " << sizeof(int*) << ' ' << sizeof(p) << '\n';
}

int main() {
	int var = 17;
	int* pr = &var;
	cout << pr << " " << *pr << endl;
	var = 19;
	cout << pr << " " << *pr << endl;
	*pr = 20;
	cout << pr << " " << *pr << endl;

	//var = pr; // error: can’t assign an int* to an int
	//pr = var;	// error: can’t assign an int to an int*

	sizes('a', 2, pr);

	return 0;
}
