#include "../std_lib_facilities.h"

template <typename T, int N> 				// requires Element<T>()
struct myArray { 					// not quite the standard array
	using value_type = T;
	using iterator = T*;
	using const_iterator = const T*;
	using size_type = unsigned int; 			// the type of a subscript
	T elems[N];
	// no explicit construct/copy/destroy needed
	iterator begin() { return elems; }
	const_iterator begin() const { return elems; }
	iterator end() { return elems + N; }
	const_iterator end() const { return elems + N; }
	size_type size() const { return size_type; }
	T& operator[] (int n) { return elems[n]; }
	const T& operator[] (int n) const { return elems[n]; }
	const T& at(int n) const; 				// range-checked access
	T& at(int n); 					// range-checked access
};

template<typename Iter>
Iter high(Iter first, Iter last) { // return an iterator to the element in [first:last) that has the highest value
	Iter high = first;
	for (Iter p = first; p != last; ++p) {
		//cout << *p;
		if (*high < *p)
			high = p;
	}
	return high;
}

void f() {
	myArray<double, 6> a = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5 };
	myArray<double, 6>::iterator p = high(a.begin(), a.end());
	cout << "the highest value was " << *p << '\n';
}

int main() {
	f();

	return 0;
}
