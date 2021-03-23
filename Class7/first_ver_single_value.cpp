#include "../std_lib_facilities.h"

int main1() {
	cout << "Please enter an integer in this range [1:10]" << endl;

	int n;

	while (cin >> n) {
		if (n < 1 || n > 10)
			cout << n << ", Integer is not in range [1:10]" << endl;
		else
			break;
	}
	
	return 0;
}