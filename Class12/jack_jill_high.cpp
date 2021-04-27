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

void fct() {
	int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);
	vector<double>* jill_data = get_from_jill();
	// . . . process . . .
	double h = -1;
	double* jack_high = 0; 					// jack_high will point to the element with the highest value
	double* jill_high = 0; 					// jill_high will point to the element with the highest value
	for (int i = 0; i < jack_count; ++i)
		if (h < jack_data[i]) {
			jack_high = &jack_data[i]; 		// save address of largest element
			h = jack_data[i]; 			// update “largest element”
		}

	h = -1;
	//for (int i = 0; i< jill_data ->size(); ++i)
	//	if (h < (*jill_data)[i]) {
	//		jill_high = &(*jill_data)[i]; 		// save address of largest element
	//		h = (*jill_data)[i]; 			// update “largest element”

	vector<double> v = *jill_data;
	for (int i = 0; i < v.size(); i++) {
		if (h < v[i]) {
			jill_high = &v[i];
			h = v[i];
		}
	}

	if (jack_high && jill_high)
		cout << "Jill's max: " << *jill_high << ";\nJack's max: " << *jack_high;
	else
		cout << "Either one is a null pointer." << endl;

	delete[] jack_data;
	delete jill_data;
}

int main() {
	fct();

	return 0;
}