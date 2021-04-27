#include "../std_lib_facilities.h"

using Line = vector<char>;         // a line is a vector of characters

class Text_iterator {
    list<Line>::iterator ln;
    Line::iterator pos;
public:
    // start the iterator at line ll’s character position pp:
    Text_iterator(list<Line>::iterator ll, Line::iterator pp) :ln{ ll }, pos{ pp } { }
    char& operator*() { return *pos; }
    Text_iterator& operator++();
    bool operator==(const Text_iterator& other) const { return ln == other.ln && pos == other.pos; }
    bool operator!=(const Text_iterator& other) const { return !(*this == other); }
};

Text_iterator& Text_iterator::operator++()
{
    ++pos;                              // proceed to next character
    if (pos == (*ln).end()) {
        ++ln;                           // proceed to next line
        pos = (*ln).begin();            // bad if ln==line.end(); so prevent
    }
    return *this;
}

struct Document {
    list<Line> line;               // a document is a list of lines
    Document() { line.push_back(Line{}); }

    Text_iterator begin(){               // first character of first line
        return Text_iterator(line.begin(), (*line.begin()).begin());
    }

    Text_iterator end(){                 // one beyond last char of last line
        auto last = line.end();
        --last;                         // we know document is not empty
        return Text_iterator(last, (*last).end());
    }
};

istream& operator>>(istream& is, Document& d)
{
    for (char ch; is.get(ch); ) {
        d.line.back().push_back(ch);    // add the character
        if (ch == '\n')
            d.line.push_back(Line{});   // add another line
    }
    if (d.line.back().size()) 
        d.line.push_back(Line{});       // add empty last line


    return is;
}

void print(Document& d)
{
    for (auto p : d) 
        cout << p;
    cout << endl;
}

void erase_line(Document& d, int n)
{
    if (n < 0 || d.line.size() - 1 <= n) 
        return;
    auto p = d.line.begin();
    advance(p, n);
    d.line.erase(p);
}

template<typename Iter>         // requires Forward_iterator<Iter>
void advance(Iter& p, int n)
{
    while (0 < n) { 
        ++p; 
        --n; 
    }
}

bool match(Text_iterator p, Text_iterator last, const std::string& s)
{
    for (auto q = s.begin(); q != s.end(); ++q) {
        if (*q != *p || p == last) 
            return false;
        ++p;
    }
    return true;
}

Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s)
{
    if (s.size() == 0) 
        return last;     // can't find an empty string

    char first_char = s[0];
    while (true) {
        auto p = find(first, last, first_char);
        if (p == last || match(p, last, s)) 
            return p;
        first = ++p;                    // look at next character
    }
}

int main() {
    try {
        Document my_doc;
        istringstream iss{ "This is a line.\nThis is a new line." };
        iss >> my_doc;
        print(my_doc);

        Text_iterator temp = find_txt(my_doc.begin(), my_doc.end(), "This");

        if (temp == my_doc.end())
            cout << "not found!" << endl;
        else {
            // Do something!
        }
    }
    catch (exception& e) {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }
    catch (...) {
        cerr << "Don't know" << endl;
        return 2;
    }
}