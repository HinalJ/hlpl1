#include "../std_lib_facilities.h"

int main() {
	
	//Pointers
	cout << "Pointers: " << endl;
	int x = 10;
	int* pr1 = &x;
	cout << x << " " << *pr1 << endl;
	int y = *pr1;
	*pr1 = 15;
	int* pr2 = &y;
	cout << x << " " << *pr1 << " " << y << " " << *pr2 << endl;
	pr1 = pr2;
	cout << x << " " << *pr1 << " " << y << " " << *pr2 << endl;
	cout << pr1 << " " << pr2 << endl;
	*pr1 = 20;
	cout << x << " " << *pr1 << " " << y << " " << *pr2 << endl;
	cout << pr1 << " " << pr2 << endl;

	//References
	cout << "References: " << endl;
	int i = 10;
	int& ref1 = i;
	cout << i << " " << ref1 << endl;
	ref1 = 15;
	int j = ref1;
	int& ref2 = j;
	cout << i << " " << ref1 << " " << j << " " << ref2 << endl;
	ref2 = ref1;
	cout << i << " " << ref1 << " " << j << " " << ref2 << endl;
	cout << &ref1 << " " << &ref2 << endl;
	ref1 = 20;
	cout << i << " " << ref1 << " " << j << " " << ref2 << endl;
	cout << &ref1 << " " << &ref2 << endl;
	// ref1 = &j;		You cannot change the value of a reference

	return 0;
}