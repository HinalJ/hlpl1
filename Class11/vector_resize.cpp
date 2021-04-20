#include "../std_lib_facilities.h"

class our_vector {
	size_t sz;
	double* elem;
	size_t space;

public:
	our_vector() :sz{ 0 }, elem{ nullptr }, space{ 0 } {};			//Default Constructor

	explicit our_vector(size_t s);						//Normal Constructor

	our_vector(const our_vector& vec);					//Copy constructor

	our_vector& operator=(const our_vector& vec);				//Copy Assignment

	our_vector(our_vector&& vec);						//Move Constructor

	our_vector& operator=(our_vector&& vec);				//Move Assignment

	~our_vector() {								//Destructor
		delete[] elem;
	}

	double& operator[](int n) { return elem[n]; }				//For non-const vectors

	int size() const { return sz; };

	void print();

	void reserve(int newalloc);

	int capacity() const { return space; }

	void resize(int newsize);

	void push_back(double d);

	double at(int n) {
		if (n < 0 || n >= sz)
			throw std::out_of_range("It is our of range access!");
		return elem[n];
	}
};

our_vector::our_vector(size_t s) :sz{ s }, elem{ new double[sz] }, space{ s }{					//Normal Constructor
	for (int i = 0; i < sz; i++)
		elem[i] = 0.0;
}

our_vector::our_vector(const our_vector& vec) : sz{ vec.sz }, elem{ new double[vec.sz] }, space{ vec.sz } {	//Copy constructor
	copy(vec.elem, vec.elem + sz, elem);
}

//we optimize this assignment

/*our_vector& our_vector::operator=(const our_vector& a) {		//Copy assignment
	double* p = new double[a.sz]; 					// allocate new space
	copy(a.elem, a.elem + a.sz, p); 				// copy elements
	delete[] elem; 							// deallocate old space
	elem = p; 							// now we can reset elem
	sz = a.sz;
	return *this; 							// return a self-reference
}*/

our_vector& our_vector::operator=(const our_vector& vec) {
	if (this == &vec)
		return *this;
	if (vec.sz <= space) {
		for (int i = 0; i < vec.sz; i++)
			elem[i] = vec.elem[i];
		sz = vec.sz;
		return *this;
	}

	double* p = new double[vec.sz]; 				// allocate new space
	copy(vec.elem, vec.elem + vec.sz, p); 				// copy elements
	delete[] elem; 							// deallocate old space
	space = sz = vec.sz;
	elem = p; 							// now we can reset elem
	return *this; 							// return a self-reference

}

our_vector::our_vector(our_vector&& vec) : sz{ vec.sz }, elem{ vec.elem }, space{ vec.space } {		//Move Constructore
	vec.sz = 0;
	vec.elem = nullptr;
}

our_vector& our_vector::operator=(our_vector&& vec) {			//Move Assignment
	delete[] elem; 							// deallocate old space
	elem = vec.elem; 						// copy a’s elem and sz
	sz = vec.sz;
	space = vec.space;
	vec.elem = nullptr; 						// make a the empty vector
	vec.sz = 0;
	return *this; 							// return a self-reference

}

void our_vector::reserve(int newalloc) {				//reserve
	if (newalloc <= space) return; 					// never decrease allocation
	double* p = new double[newalloc]; 				// allocate new space
	for (int i = 0; i < sz; ++i) p[i] = elem[i]; 			// copy old elements
	delete[] elem; 							// deallocate old space
	elem = p;
	space = newalloc;
}

void our_vector::resize(int newsize) {
	reserve(newsize);
	for (int i = sz; i < newsize; i++)
		elem[i] = 0;
	sz = newsize;
}

void our_vector::push_back(double d) {  				//increase vector size by one; initialize the new element with d
	if (space == 0)
		reserve(8); 						// start with space for 8 elements
	else if (sz == space)
		reserve(2 * space); 					// get more space
	elem[sz] = d; 							// add d at end
	++sz; 								// increase the size (sz is the number of elements)
}


void our_vector::print() {
	for (int i = 0; i < sz; i++) {
		cout << elem[i] << " ";
	}
	cout << endl;
}

int main() {
	// We can optimize this code of resize:
	// std Vector implementations keep track of both the number of elements and 
	// an amount of “free space” reserved for future expansion

	/*vector<double>* p = new vector<double>(5);
	int n = 0; // number of elements
	for (double d; cin >> d; ) {
		if (n == p-> size()) {
			vector<double>* q = new vector<double>(p-> size() * 2);
			copy(p-> begin(), p-> end(), q-> begin());
			delete p;
			p = q;
		}
		(*p)[n] = d;
		++n;
	}*/

	try {
		our_vector p(2);
		p[0] = 1.0;
		p[1] = 2.0;

		cout << p.at(3) << endl;
	}
	catch (out_of_range e) {
		cout << e.what() << endl;
	}

	our_vector* n_p = new our_vector();
	cout << n_p->size() << endl;
	cout << n_p->capacity() << endl;

	n_p->resize(10);
	cout << n_p->size() << endl;
	cout << n_p->capacity() << endl;

	n_p->push_back(2);

	cout << n_p->size() << endl;
	cout << n_p->capacity() << endl;
	n_p->print();

	//Copy check
	our_vector* copy_p(n_p);
	cout << copy_p->size() << endl;
	cout << copy_p->capacity() << endl;
	copy_p->print();

	our_vector* copy_assign = copy_p;
	cout << copy_assign->size() << endl;
	cout << copy_assign->capacity() << endl;
	copy_assign->print();

	return 0;
}