#include "../std_lib_facilities.h"

class our_vector {
	size_t sz;
	double* elem;

public:
	our_vector(size_t s);								//Default Constructor

	our_vector(initializer_list<double> st);			//Initialise with elements given

	our_vector(const our_vector& vec);					//Copy constructor

	~our_vector() {										//Destructor
		delete[] elem;
	}								

	double get(size_t n) const {						//Getter
		return elem[n];
	}

	void set(size_t n, double v) {						//Setter
		elem[n] = v;
	}

	int size() const { return sz; };
	
	void print();
};

our_vector::our_vector(size_t s) :sz{ s }, elem{ new double[sz] }{
	for (int i = 0; i < sz; i++)
		elem[i] = 0.0;
}

our_vector::our_vector(initializer_list<double> st) : sz{ st.size() }, elem{ new double[sz] } {
	copy(st.begin(), st.end(), elem);
}

our_vector::our_vector(const our_vector& vec) : sz{ vec.sz }, elem{ new double[vec.sz] } {
	copy(vec.elem, vec.elem + sz, elem);
}

void our_vector::print() {
	for (int i = 0; i < sz; i++) {
		cout << elem[i] << " ";
	}
	cout << endl;
}

int main() {
	our_vector v1(4);
	our_vector v2{ 1, 2, 3 };
	our_vector v3{ v2 };

	v1.print();
	v2.print();
	v3.print();

	v2.set(0, 20);

	v1.print();
	v2.print();
	v3.print();

	//v2 = v1 We still cannot use this expression, because we didn't yet define for assignement.


	return 0;
}