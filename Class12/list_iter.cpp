#include "../std_lib_facilities.h"

template<typename Elem>
struct Link {
	Link<Elem>* prev; // previous link
	Link<Elem>* succ; // successor (next) link
	Elem val; // the value

	Link(const Elem& v = Elem{ 0 }, Link<Elem>* p = nullptr, Link<Elem>* s = nullptr)
		: val{ v }, prev{ p }, succ{ s } { }
};

template<typename Elem> struct myList {
	Link<Elem>* first;
	Link<Elem>* last; // one beyond the last link

public:
	myList() : first(nullptr), last(nullptr) {};

	class iterator;
	iterator begin() { return iterator(first); };
	iterator end() { return iterator(last->succ); };
	iterator insert(iterator p, const Elem& v);
	iterator erase(iterator p);
	void push_front(const Elem& v);
	void push_back(const Elem& v);
	void pop_front();
	void pop_back();
	Elem& front() { return first->val; };
	Elem& back() { return last->val; };
};

template<typename Elem> 
class myList<Elem>::iterator {
	Link<Elem>* curr; // current link
public:
	iterator(Link<Elem>* p) :curr{ p } {}
	iterator& operator++() { curr = curr-> succ; return *this; } // forward
	iterator& operator--() { curr = curr-> prev; return *this; } // backward
	Elem& operator*() { return curr-> val; } // get value (dereference)
	bool operator==(const iterator& b) const { return curr == b.curr; }
	bool operator!= (const iterator& b) const { return curr != b.curr; }
};

template<typename Elem> 
typename myList<Elem>::iterator myList<Elem>::insert(myList<Elem>::iterator p, const Elem& val) {				//add val after p
	Link<Elem>* ptr = new Link<Elem>{ val, p, p->succ };
	
	p->succ = ptr;
	if(ptr->succ)
		ptr->succ->prev = ptr;

	return iterator(ptr);
}

template<typename Elem>
typename myList<Elem>::iterator myList<Elem>::erase(myList<Elem>::iterator p) {		//remove p from the list
	if (p == nullptr)
		return nullptr;

	if (p->prev)
		p->prev->succ = p->succ;
	if (p->succ)
		p->succ->prev = p->prev;

	return itertor(p);
}

template <typename Elem>
void typename myList<Elem>::push_front(const Elem& v) {
	Link<Elem>* ptr = new Link<Elem>{ v, nullptr, first };
	if (last == nullptr)
		last = ptr;

	if (first != nullptr)
		first->prev = ptr;

	first = ptr;
}

template <typename Elem>
void typename myList<Elem>::push_back(const Elem& v) {
	Link<Elem>* ptr = new Link<Elem>{ v, last, nullptr };
	if (first == nullptr) 
		first = ptr;
	
	if (last != nullptr)
		last->succ = ptr;

	last = ptr;
}

template <typename Elem>
void typename myList<Elem>::pop_front() {
	Link<Elem>* tmp = first->succ;
	delete first;
	first = tmp;
}

template <typename Elem>
void typename myList<Elem>::pop_back() {
	Link<Elem>* tmp = last->prev;
	delete last;
	last = tmp;
}

template<typename Iter>
void print_all(Iter first, Iter last) {
	for (Iter p = first; p != last; ++p) 
		cout << *p << " ";
	cout << endl;

}
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

int main() {
	
	myList<int> li;
	li.push_back(1);
	li.push_back(2);
	li.push_back(3);
	li.push_front(4);

	myList<int>::iterator p = high(li.begin(), li.end());
	cout << "the highest value was " << *p << '\n'; 

	print_all(li.begin(), li.end());
	cout << li.front() << " " << li.back() << endl;

	li.pop_front();
	p = high(li.begin(), li.end());
	cout << "the highest value was " << *p << '\n';

	print_all(li.begin(), li.end());

	li.pop_back();
	p = high(li.begin(), li.end());
	cout << "the highest value was " << *p << '\n';

	print_all(li.begin(), li.end());

	cout << endl;

	return 0;
}