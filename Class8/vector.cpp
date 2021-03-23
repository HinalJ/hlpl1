#include "../std_lib_facilities.h"

class our_vector {
	int sz;
	double* elem;

public:
	our_vector(int s) :sz{ s }, elem{ new double[s] } 		
	{ 
		for (int i = 0; i < s; ++i) 
			elem[i] = 0; 
	}
	int size() const { return sz; };
	~our_vector() {
		delete[] elem;
	}
	double get(int n) const { 
		return elem[n]; 
	} 		
	void set(int n, double v) {
		elem[n] = v; 
	} 	

};

int main() {
	our_vector v(5);
	for (int i = 0; i < v.size(); i++) {
		v.set(i, 1.1 * i);
		cout << "v[" << i << "]==" << v.get(i) << '\n';
	}

	//Pointers to Class Objects
	our_vector* pr = new our_vector(5);
	int x = pr->size();
	double d = pr->get(3);
	cout << x << " " << d << endl;

	return 0;
}