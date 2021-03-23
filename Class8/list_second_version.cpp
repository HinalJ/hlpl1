#include "../std_lib_facilities.h"

struct Link {
	string value;
	Link* prev;
	Link* succ;
	Link(const string& v, Link* p = nullptr, Link* s = nullptr)
		:value(v), prev(p), succ(s) {};
};

Link* insert(Link* p, Link* n) {				//n before p
	if (n == nullptr)
		return p;
	if (p == nullptr)
		return n;
	
	n->succ = p;
	if(p->prev)
		p->prev->succ = n;
	n->prev = p->prev;
	p->prev = n;
	
	return n;
}
/* Next Step: 
* add: insert after an element								//Try This
* erase: remove an element
* find: find a Link with a given value
* advance: get the nth successor
*/ 

int main() {
	Link* norse_gods = new Link{ "Thor"};
	norse_gods = insert(norse_gods, new Link{ "Odin" });
	norse_gods = insert(norse_gods, new Link{ "Freia" });


	while (norse_gods) {
		cout << norse_gods->value << " ";
		if(norse_gods->prev!=nullptr)
			cout << norse_gods->prev->value << " " ;
		if (norse_gods->succ != nullptr)
			cout << norse_gods->succ->value << endl;

		norse_gods = norse_gods->succ;
	}
	cout << endl;

	return 0;
}

