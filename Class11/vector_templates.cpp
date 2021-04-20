#include "../std_lib_facilities.h"

template<typename T, typename A = allocator<T>>
class our_vector {
	A alloc;
	size_t sz;
	T* elem;
	size_t space;

public:
	our_vector() :sz{ 0 }, elem{ nullptr }, space{ 0 } {};				//Default Constructor

	explicit our_vector(size_t s) :sz{ s }, elem{ alloc.allocate(s)}, space{ s }{ 	//Normal Constructor
		for (T* p = elem; p != elem + s; p++)
			alloc.construct(p, T());
	}

	our_vector(const our_vector<T, A>& vec);					//Copy constructor

	our_vector<T, A>& operator=(const our_vector<T, A>& vec);			//Copy Assignment

	our_vector(our_vector<T, A>&& vec);						//Move Constructor

	our_vector<T, A>& operator=(our_vector<T, A>&& vec);				//Move Assignment

	~our_vector() {									//Destructor
		for (int i = 0; i < sz; ++i) 						
			alloc.destroy(&elem[i]);
		alloc.deallocate(elem, space);
	}

	T& operator[](int n) { return elem[n]; }					//For non-const vectors

	int size() const { return sz; };

	void print();

	void reserve(int newalloc);

	int capacity() const { return space; }

	void resize(int newsize, T val = T());

	void push_back(T& val);

	T& at(int n) {
		if (n < 0 || sz < n)
			throw std::out_of_range("It is out of range access!");
		return elem[n];
	}
};

template<typename T, typename A> our_vector<T, A>::our_vector(const our_vector<T, A>& vec) : sz{ vec.sz }, elem{ alloc.allocate(sz) }, space{ vec.sz } {	//Copy constructor
	copy(vec.elem, vec.elem + sz, elem);
}

template<typename T, typename A> our_vector<T, A>& our_vector<T, A>::operator=(const our_vector<T, A>& vec) {
	if (this == &vec)
		return *this;
	if (vec.sz <= space) {								//never decrease deallocation
		copy(vec.elem, vec.elem + vec.sz, elem);
		/*for (int i = 0; i < vec.sz; i++)
			elem[i] = vec.elem[i];*/
		for (int i = vec.sz; i < sz; ++i) 
			alloc.destroy(&elem[i]);
		sz = vec.sz;
		return *this;
	}

	T* p = alloc.allocate(vec.sz); 							// allocate new space
	copy(vec.elem, vec.elem + vec.sz, p); 						// copy elements
	for (int i = 0; i < sz; ++i) 							// deallocate old space
		alloc.destroy(&elem[i]);
	alloc.deallocate(elem, space);
	space = sz = vec.sz;
	elem = p; 									// now we can reset elem
	return *this; 									// return a self-reference

}

template<typename T, typename A> our_vector<T,A>::our_vector(our_vector<T, A>&& vec) : sz{ vec.sz }, elem{ vec.elem }, space{ vec.space } {		//Move Constructore
	vec.sz = 0;
	vec.elem = nullptr;
}

template<typename T, typename A> our_vector<T, A>& our_vector<T, A>::operator=(our_vector<T, A>&& vec) {		//Move Assignment
	for (int i = 0; i < sz; ++i) 											// deallocate old space
		alloc.destroy(&elem[i]);
	alloc.deallocate(elem, space);
	elem = vec.elem; 			// copy a’s elem and sz
	sz = vec.sz;
	space = vec.space;
	vec.elem = nullptr; 		// make a the empty vector
	vec.sz = 0;
	return *this; 			// return a self-reference

}

template<typename T, typename A> void our_vector<T, A>::reserve(int newalloc) {		//reserve
	if (newalloc <= space) return; 							// never decrease allocation
	T* p = alloc.allocate(newalloc); 						// allocate new space
	for (int i = 0; i < sz; ++i)
		alloc.construct(&p[i], elem[i]);					// copy old elements
	for (int i = 0; i < sz; ++i) 							// deallocate old space
		alloc.destroy(&elem[i]);
	alloc.deallocate(elem, space);
	elem = p;
	space = newalloc;
}

template<typename T, typename A> void our_vector<T, A>::resize(int newsize, T val) {
	reserve(newsize);
	for (int i = sz; i < newsize; i++)
		alloc.construct(&elem[i], val);
	for (int i = newsize; i < sz; i++)
		alloc.destroy(&elem[i]);
	sz = newsize;
}

template<typename T, typename A> void our_vector<T, A>::push_back(T& val) {  		//increase vector size by one; initialize the new element with d
	if (space == 0)
		reserve(8); 								// start with space for 8 elements
	else if (sz == space)
		reserve(2 * space); 							// get more space
	alloc.construct(&elem[sz], val);
	++sz; 										// increase the size (sz is the number of elements)
}

template<typename T, typename A> void our_vector<T, A>::print() {
	for (int i = 0; i < sz; i++) {
		cout << elem[i] << " ";
	}
	cout << endl;
}

int main() {
	try {
		our_vector<string> p(2);
		p[0] = "first";
		p[1] = "second";

		cout << p.at(3)<< endl;
	}
	catch(out_of_range e){
		cout << e.what() << endl;
	}
	
	our_vector<double>* n_p = new our_vector<double>();
	cout << n_p->size() << endl;
	cout << n_p->capacity() << endl;

	n_p->resize(10);
	cout << n_p->size() << endl;
	cout << n_p->capacity() << endl;

	double x = 2;
	n_p->push_back(x);

	cout << n_p->size() << endl;
	cout << n_p->capacity() << endl;
	n_p->print();

	//Copy check
	our_vector<double>* copy_p(n_p);
	cout << copy_p->size() << endl;
	cout << copy_p->capacity() << endl;
	copy_p->print();

	our_vector<double>* copy_assign = copy_p;
	cout << copy_assign->size() << endl;
	cout << copy_assign->capacity() << endl;
	copy_assign->print();
		


	return 0;
}