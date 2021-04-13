#include "../std_lib_facilities.h"

class our_vector {
	size_t sz;
	double* elem;
	
public:
	our_vector(size_t s) :sz{ s }, elem{ new double[sz] }
	{
		for (int i = 0; i < sz; i++)
			elem[i] = 0.0;
	}

	our_vector(initializer_list<double> st) :sz{ st.size() }, elem{ new double[sz] } 
	{
		copy(st.begin(), st.end(), elem);
	}

	int size() const { return sz; };
	~our_vector() {
		delete[] elem;
	}
	double get(size_t n) const {
		return elem[n];
	}
	void set(size_t n, double v) {
		elem[n] = v;
	}

	void print() {
		for (int i = 0; i < sz; i++) {
			cout << elem[i] << " ";
		}
		cout << endl;
	}
};

int main() {
	our_vector v1 (4);
	our_vector v2 { 1, 2, 3 };

	v1.print();
	v2.print();

	// v2 = v1 // They will share elements, will have same memory, if we delete v1,v2, is also gone.
	// At this point it gives assertion error as well. So, how to copy?
	v1.set(0, 2);
	
	v1.print();
	v2.print();

	return 0;
}