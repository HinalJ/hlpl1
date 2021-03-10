#include "std_lib_facilities.h"

void encode() {
	vector<vector<int>> numbers;

	int test_cases = 0, size = 0, n = 0;
	cout << "Please write number of test cases (+ve Integer): ";
	cin >> test_cases;
	if (!cin || test_cases <= 0) 
		error("Test case should be positive integer!");
	
	cout << "Total Number in line and then type numbers itself!" << endl;

	for (int i = 0; i < test_cases; i++) {
		vector<int> num_in_line;
		cin >> size;
		if (!cin || size <= 0) 
			error("Total size of numbers to add in line should be positive integer!");
		
		for (int j = 0; j < size; j++) {
			cin >> n;
			if (!cin || n <= 0)
				error("Bad input of numbers! Either one or more written numbers are not +ve integers!");
			num_in_line.push_back(n);
		}
		sort(num_in_line.begin(), num_in_line.end());
		numbers.push_back(num_in_line);
	}

	for (vector<int> line: numbers) {
		for (int i = 0; i < line.size(); i++) {
			cout << string(line[i], '1');
			if(i!=line.size()-1)
				cout << '-';
		}
		cout << endl;
	}
}

void decode() {
	vector<vector<int>> numbers;

	int test_cases = 0, size = 0, n=0;
	string str_num, temp;

	cout << "Please write number of test cases (+ve Integer): ";
	cin >> test_cases;
	if (!cin || test_cases <= 0)
		error("Test case should be positive integer!");

	cout << "Total Number in line and then type encoded numbers itself!" << endl;

	for (int i = 0; i < test_cases; i++) {
		vector<int> num_in_line;
		cin >> size;
		if (!cin || size <= 0)
			error("Total size of encoded numbers to add in line should be positive integer!");

		for (int j = 0; j < size; j++) {
			cin >> n;
			if (!cin || n <= 0)
				error("Bad input of numbers! Either one or more written numbers are not +ve integers!");
			
			str_num = to_string(n);
			temp = string(str_num.size(), '1');

			if (temp != str_num)
				error("You can just enter digit 1 and nothing else!");

			num_in_line.push_back(str_num.size());
		}
		sort(num_in_line.begin(), num_in_line.end());
		numbers.push_back(num_in_line);
	}

	for (vector<int> line : numbers) {
		for (int i = 0; i < line.size(); i++) {
			cout << line[i];
			if (i != line.size() - 1)
				cout << '-';
		}
		cout << endl;
	}
}

int main() {
	try {
		cout << "You want to encode or decode ?" << endl;
		cout << "1 Encode" << endl;
		cout << "2 Decode" << endl;
		cout << "Choose 1 or 2!" << endl;
		int choice = 0;
		cin >> choice;

		switch (choice) {
		case 1:
			encode();
			break;

		case 2:
			decode();
			break;
		default:
			error("Choose from two options!");
		}
		return 0;

	}
	catch (exception& e) {
		cout << e.what() << endl;
		return 1;
	}

}
