#include "../std_lib_facilities.h"

double* get_from_jack(int* count) {
	if (!count)
		return 0;

	const int n = 20;
	//let's set for first 20;
	*count = n;
	double* arr = new double[*count];

	for (int i = 0; i < *count; i++)
		arr[i] = i;

	return arr;
}

vector<double>* get_from_jill() {
	vector<double>* vec = new vector<double>;
	const int n = 20;
	//let's set for first 20;

	for (int i = 0; i < n; i++)
		vec->push_back(i);
	return vec;
}

template<typename Iterator>
Iterator high(Iterator first, Iterator last) { // return an iterator to the element in [first:last) that has the highest value
	Iterator high = first;
	for (Iterator p = first; p != last; ++p)
		if (*high < *p) high = p;
	return high;
}

void fct() {
	int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);
	vector<double>* jill_data = get_from_jill();

	double* jack_high = high(jack_data, jack_data + jack_count);
	vector<double>& v = *jill_data;
	double* jill_high = high(&v[0], &v[0] + v.size());

	cout << "Jill's max: " << *jill_high << ";\nJack's max: " << *jack_high;

	delete[] jack_data;
	delete jill_data;
}

int main() {
	fct();

	return 0;
}