#include "../std_lib_facilities.h"

vector<int>& ff() {
	vector<int> abc(7);			//abc created
	return abc;				//abc destroyed
}

int main() {

	int arr[] = { 1,2,3 };
	int* p = arr;

	for (int* p = &arr[0]; p < &arr[3]; p++)
		cout << *p << " ";

	cout << endl;

	char str[] = "Programming"; // 'P', 'r', ........'g', '0' //12 chars to stor 11 chars

	//char abc[] = { 'a', 'b', 'c' }; // No terminating 0

	cout << strlen(str) << endl;		

	//vector<int>& ptr1 = ff();
	//cout << ptr1[2] << endl; //Since abc was destroyed we cannot access it.


	return 0;
}