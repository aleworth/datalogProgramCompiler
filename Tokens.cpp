#include "Tokens.h"



Tokens::~Tokens()
{
}

/*void Tokes::addCharToMap(char value) {
	tokenType toke;
	stringstream test;
	test << value;

	switch (value) {
	case ':': toke = COLON; myMap[test.str()] = toke;
	case '.': toke = PERIOD; myMap[test.str()] = toke;
	case '?': toke = Q_MARK; myMap[test.str()] = toke;
	case '(': toke = RIGHT_PAREN; myMap[test.str()] = toke;
	case ')': toke = LEFT_PAREN; myMap[test.str()] = toke;
	case ',': toke = COMMA; myMap[test.str()] = toke;
	case '*': toke = MULTIPLY; myMap[test.str()] = toke;
	case '+': toke = ADD; myMap[test.str()] = toke;
	case '$': toke = UNDEFINED; myMap[test.str()] = toke;
	case '&': toke = UNDEFINED; myMap[test.str()] = toke;
	case '^': toke = UNDEFINED; myMap[test.str()] = toke;
	}
};

void Tokes::addKeyToMap(string value) {
	tokenType toke;

	if (value == "Schemes") {
		toke = SCHEMES;
	}
	else if (value == "Facts") {
		toke = FACTS;
	}
	else if (value == "Rules") {
		toke = RULES;
	}
	else if (value == "Queries") {
		toke = QUERIES;
	}
	myMap[value] = toke;
};

void Tokes::addIDToMap(string value) {
	tokenType toke = ID;
	myMap[value] = toke;
};

void Tokes::addComToMap(string value) {
	tokenType toke = COMMENT;
	myMap[value] = toke;
};

void Tokes::addUnToMap(string value) {
	tokenType toke = UNDEFINED;
	myMap[value] = toke;
};

void Tokes::addEOFToMap(char x) {
	tokenType toke = MYEOF;
	stringstream test;
	test << x;

	myMap[test.str()] = toke;

};*/

void Tokens::toString(Tokens failure) {
	cout << "  ";
	cout << "(" << failure.type;
	cout << ",\"" << failure.value << "\"";
	cout << "," << failure.lineNum;
	cout << ")" << endl;
}
