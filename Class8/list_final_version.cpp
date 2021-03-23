#include "../std_lib_facilities.h"

class Link {
private:
	Link* prev;
	Link* succ;
public:
	string value;
	Link(const string& v, Link* p = nullptr, Link* s = nullptr)
		:value(v), prev(p), succ(s) {};
	Link* insert(Link* n);
	Link* erase();
	Link* find(const string& s);
	Link* advance(int n);
	void print_all();
	Link* next() const{ return succ; }
	Link* previous() const{ return prev; }
};

Link* Link::insert(Link* n) {				//n before p
	if (n == nullptr)
		return this;
	if(this == nullptr)
		return n;

	n->succ = this;
	n->prev = prev;
	if (prev)
		prev->succ = n;
	prev = n;

	return n;
}

Link* Link::erase() {
	if (this == nullptr) return nullptr;
	if (prev)
		prev->succ = succ;
	if (succ)
		succ->prev = prev;
	return succ;
}

Link* Link::find(const string& s) {
	Link* temp = this;
	if (temp == nullptr)
		return nullptr;
	while (temp) {
		if (temp->value == s)
			return temp;
		temp = temp->succ;
	}

	return nullptr;
}

Link* Link::advance(int n) {
	Link* pr = this;
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

void Link::print_all() {
	cout << "{";
	Link* pr = this;
	while (pr) {
		cout << pr->value;
		if (pr = pr->succ) {
			cout << ", ";
		}
	}
	cout << "}\n";
}

int main() {
	Link* norse_gods = new Link("Thor");
	norse_gods = norse_gods->insert(new Link{ "Odin" });
	norse_gods = norse_gods->insert(new Link{ "Zeus" });
	norse_gods = norse_gods->insert(new Link{ "Freia" });

	Link* greek_gods = new Link("Hera");
	greek_gods = greek_gods->insert(new Link{ "Athena" });
	greek_gods = greek_gods->insert(new Link{ "Mars" });
	greek_gods = greek_gods->insert(new Link{ "Poseidon" });

	norse_gods->print_all();
	greek_gods->print_all();

	Link* mars_pos = greek_gods->find("Mars");
	mars_pos->value = "Ares";
	
	Link* zeus_link = norse_gods->find("Zeus");
	if (zeus_link) {
		if (zeus_link == norse_gods)
			norse_gods = norse_gods->next();
		
		zeus_link->erase();
		greek_gods = greek_gods->insert(zeus_link);
	}

	norse_gods->print_all();
	greek_gods->print_all();

	Link* temp = norse_gods->advance(2);
	temp->print_all();

	cout << endl;

	return 0;
}

