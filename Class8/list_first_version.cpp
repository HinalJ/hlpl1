#include "../std_lib_facilities.h"

struct Link {
	string value;
	Link* prev;
	Link* succ;
	Link(const string& v, Link* p = nullptr, Link* s = nullptr)
		:value(v), prev(p), succ(s) {};
};

int main() {
	Link* norse_gods = new Link{ "Thor",nullptr,nullptr };
	norse_gods = new Link{ "Odin",nullptr,norse_gods };
	norse_gods -> succ -> prev = norse_gods;
	norse_gods = new Link{ "Freia",nullptr,norse_gods };
	norse_gods -> succ -> prev = norse_gods;

	while (norse_gods) {
		cout << norse_gods->value << " ";
		norse_gods = norse_gods->succ;
	}
	cout << endl;

	return 0;
}