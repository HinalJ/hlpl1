#include "../std_lib_facilities.h"

//Using Strings
bool is_palindrome(const string& s) {
	int first = 0; 								// index of first letter
	int last = s.length()-1; 					// index of last letter
	while (first < last) { 						// we haven’t reached the middle
		if (s[first] != s[last]) return false;
		++first; 								// move forward
		--last; 								// move backward
	}
	return true;
}

//Using Arrays
bool is_palindrome(const char s[], int n) { 	// s points to the first character of an array of n characters
	int first = 0; 								// index of first letter
	int last = n-1; 							// index of last letter
	while (first < last) { 						// we haven’t reached the middle
		if (s[first] != s[last]) return false;
		++first; 								// move forward
		--last; 								// move backward
	}
	return true;
}

istream& read_word(istream& is, char* buffer, int max) { 	// read at most max–1 characters from is into buffer
	is.width(max); 											// read at most max–1 characters in the next >>
	is >> buffer; 											// read whitespace-terminated word,
	// add zero after the last character read into buffer
	return is;
}

//Using Pointers
bool is_palindrome(const char* first, const char* last) { 	// first points to the first letter, last to the last letter
	while (first < last) { 									// we haven’t reached the middle
		if (*first != *last) return false;
		++first; 											// move forward
		--last; 											// move backward
	}
	return true;
}


int main() {
	/*for (string s; cin >> s; ) {
		cout << s << " is";
		if (!is_palindrome(s)) cout << " not";
		cout << " a palindrome\n";
	}*/

	/*constexpr int max = 128;								//Length of word
	for (char s[max]; read_word(cin, s, max); ) {
		cout << s << " is";
		if (!is_palindrome(s, strlen(s))) cout << " not";
		cout << " a palindrome\n";
	}*/

	const int max = 128;
	for (char s[max]; read_word(cin, s, max); ) {
		cout << s << " is";
		if (!is_palindrome(&s[0], &s[strlen(s)-1])) cout << " not";
		cout << " a palindrome\n";
	}

	return 0;

}