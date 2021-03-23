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
	if (p->prev)
		p->prev->succ = n;
	n->prev = p->prev;
	p->prev = n;

	return n;
}

Link* erase(Link* p) {
	if (p == nullptr) return nullptr;
	if (p->prev)
		p->prev->succ = p->succ;
	if (p->succ)
		p->succ->prev = p->prev;
	return p->succ;

}

Link* find(Link* pr, const string& s) {
	if (pr == nullptr)
		return nullptr;
	while (pr) {
		if (pr->value == s)
			return pr;
		pr = pr->succ;
	}
	return nullptr;
}

Link* advance(Link* pr, int n) {
	if (pr == nullptr)
		return nullptr;

	if (n > 0) {
		while (n--) {
			if (pr->succ == nullptr)
				return nullptr;
			pr = pr->succ;
		}
	}
	else {
		while (n++) {
			if (pr->prev == nullptr)
				return nullptr;
			pr = pr->prev;
		}
	}
	return pr;
}

void print_all(Link* pr) {
	cout << "{";

	while (pr) {
		cout << pr->value;
		if (pr = pr->succ)
			cout << ", ";
	}
	cout << "}\n";
}

int main() {
	Link* norse_gods = new Link("Thor");
	norse_gods = insert(norse_gods, new Link{ "Odin" });
	norse_gods = insert(norse_gods, new Link{ "Zeus" });
	norse_gods = insert(norse_gods, new Link{ "Freia" });

	Link* greek_gods = new Link("Hera");
	greek_gods = insert(greek_gods, new Link{ "Athena" });
	greek_gods = insert(greek_gods, new Link{ "Mars" });
	greek_gods = insert(greek_gods, new Link{ "Poseidon" });

	print_all(norse_gods);
	print_all(greek_gods);

	Link* mars_pos = find(greek_gods, "Mars");
	mars_pos->value = "Ares";

	Link* zeus_link = find(norse_gods, "Zeus");
	if (zeus_link) {
		if (zeus_link == norse_gods)
			norse_gods = norse_gods->succ;
		erase(zeus_link);
		greek_gods = insert(greek_gods, zeus_link);
	}

	print_all(norse_gods);
	print_all(greek_gods);

	cout << endl;

	return 0;
}

