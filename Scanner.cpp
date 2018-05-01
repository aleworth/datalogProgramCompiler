#include "Scanner.h"

Scanner::Scanner()
{
}


Scanner::~Scanner()
{
}

void Scanner::createToken(string type, string value, int lineNum) {

	Tokens myToken = Tokens(type, value, lineNum);
	newVec.push_back(myToken);
};

void Scanner::printTokes() {
        for (unsigned int i = 0; i < newVec.size(); i++) {
	cout << "(" << newVec.at(i).type;
	cout << ", \"" << newVec.at(i).value << "\""
		<< ", " << newVec.at(i).lineNum << ")" << endl;
	}
};

string Scanner::eMachAlpha(char a) {
	string type = "";

	switch (a) {
		case ':': type = "COLON"; break;
		case '.': type = "PERIOD"; break;
		case '?': type = "Q_MARK"; break;
		case '(': type = "LEFT_PAREN"; break;
	}

	return type;
};

string Scanner::eMachBeta(char a) {
	string type = "";

	switch (a) {
		case ')': type = "RIGHT_PAREN"; break;
		case ',': type = "COMMA"; break;
		case '*': type = "MULTIPLY"; break;
		case '+': type = "ADD"; break;
	}

	return type;
};

string Scanner::easyMachine(char a) {
	string type = "";

	if ((a == ':')|(a == '.')|(a == '?')|(a == '(')) {
		type = eMachAlpha(a);
	}
	else {
		type = eMachBeta(a);
	}

	return type;
};

bool Scanner::isEasy(char a, int lineNumb) {
	bool check = false;
	stringstream test;
	test << a;
	string type = "";

	if ((a == ':')|(a == '.')|(a == '?')|(a == '(')|(a == ')')|(a == ',')|(a == '*')|(a == '+')) {
		type = easyMachine(a);
		check = true;
	}
	else if ((a == '$')|(a == '&')|(a == '^')) {
		string value;
		test >> value;
		isUn(value, lineNumb);
		check = true;
		return check;
	}

	if (!check) {
		return check;
	}
	else {
		createToken(type, test.str(), lineNumb);
		tokenCnt++;
	}

	return check;
};

void Scanner::idMachine(ifstream& newFile, char x, int lineNumb) {
	stringstream comment;
	bool read = true;
	comment << x;
	while (read) {
		char c = newFile.peek();
		if (isdigit(c)) {
			newFile.get(x);
			comment << x;
		}
		else if (!isalpha(c)) {
			read = false;
			break;
		}
		else if (isalpha(c)) {
			newFile.get(x);
			comment << x;
		}
		else {
			read = false;
		}
	}
	isID(comment.str(), lineNumb);
};

void Scanner::isID(string value, int lineNumb) {
	string type = "";

	if (value == "Schemes") {
		type = "SCHEMES";
	}
	else if (value == "Facts") {
		type = "FACTS";
	}
	else if (value == "Rules") {
		type = "RULES";
	}
	else if (value == "Queries") {
		type = "QUERIES";
	}
	else {
		type = "ID";
	}
	createToken(type, value, lineNumb);
	tokenCnt++;
};

int Scanner::comBlock(ifstream& newFile, char x, int lineNumb) {
	stringstream comment;
	int newLine = lineNumb;
	bool isBlock = true;
	bool isUndef = false;
	comment << x;

	while (isBlock) {
		newFile.get(x);
		char c = newFile.peek();
		if ((x == '|') && (c == '#')) {
			comment << x;
			newFile.get(x);
			comment << x;
			isBlock = false;
		}
		else if (c == -1) {
			comment << x;
			isUn(comment.str(), lineNumb);
			newFile.get(x);
			newLine = unMachine(newFile, x, newLine);
			isUndef = true;
			isBlock = false;
		}
		else {
			if (x == '\n') {
				newLine++;
				comment << x;
			}
			else {
				comment << x;
			}
		}
	}
	if (!isUndef) {
		isComment(comment.str(), lineNumb);
	}
	else {
		//do nothing;
	}

	return newLine;
};

int Scanner::commentMachine(ifstream& newFile, char x, int lineNumb) {
	bool read = true;
	bool isBlock = false;
	stringstream comment;
	comment << x;
	while (read) {
		char c = newFile.peek();
		if (c == '\n') {
			read = false;
		}
		else if ((x == '#') && (c == '|')) {
			read = false;
			isBlock = true;
		}
		else {
			newFile.get(x);
			comment << x;
		}
	}
	if(isBlock) {
		int newLine = comBlock(newFile, x, lineNumb);
		return newLine;
	}
	else {
		string commentTwo = comment.str();
		isComment(commentTwo, lineNumb);
		return lineNumb;
	}
};

void Scanner::isString(string value, int lineNumb) {
	string type = "STRING";
	createToken(type, value, lineNumb);
	tokenCnt++;
};

int Scanner::strMachine(ifstream& newFile, char x, int lineNumb) {
	stringstream comment;
	int newLine = lineNumb;
	comment << x;
	while (newFile.get(x)) {
		char c = newFile.peek();
		if (x == '\'') {
			if (c == '\'') {
				comment << x;
				newFile.get(x);
				comment << x;
			}
			else {
				comment << x;
				break;
			}
		}
		else if (c == -1) {
			comment << x;
			isUn(comment.str(), lineNumb);
			newFile.get(x);
			newLine = unMachine(newFile, x, newLine);
			return newLine;
		}
		else if (x == '\n') {
			newLine++;
			comment << x;
		}
		else {
			comment << x;
		}
	}
	isString(comment.str(), lineNumb);
	return newLine;
};

void Scanner::isComment(string value, int lineNumb) {
	string type = "COMMENT";
	//createToken(type, value, lineNumb);
	//tokenCnt++;
};

int Scanner::unMachine(ifstream& newFile, char x, int lineNumb) {
	stringstream comment;
	char c = newFile.peek();

	if (c == -1) {
		if (x == '\n') {
			lineNumb++;
		}
		else {
			//do nothing
		}
		string newX = "";
		isEOF(newX, lineNumb);
	}
	else if (x == '\n') {
		lineNumb++;
	}
	else if ((x == ':') && (c == '-')) {
		string type = "COLON_DASH";
		comment << x;
		newFile.get(x);
		comment << x;
		createToken(type, comment.str(), lineNumb);
		tokenCnt++;
	}
	else {
	bool check = isEasy(x, lineNumb);
		if (!check) {
			string type = "UNDEFINED";
			comment << x;
			createToken(type, comment.str(), lineNumb);
			tokenCnt++;
		}
		else {
			//do nothing
		}
	}

	return lineNumb;
};

void Scanner::isUn(string value, int lineNumb) {
	string type = "UNDEFINED";
	createToken(type, value, lineNumb);
	tokenCnt++;
};

void Scanner::isEOF(string x, int lineNumb) {
	string type = "EOF";
	createToken(type, x, lineNumb);
	tokenCnt++;
};

int Scanner::lineCheck(int newLine, int oldLine) {
	if (newLine != oldLine) {
		oldLine = newLine;
	}
	else {
		// do nothing
	}

	return oldLine;
}

void Scanner::scanFile(ifstream& newFile) {
	int lineNumb = 1;
	char x;
	while (newFile.get(x)) {
		//char c = newFile.peek();

		if (x == '\'') {
			int check = strMachine(newFile, x, lineNumb);
			lineNumb = lineCheck(check, lineNumb);
		}
		else if (isalpha(x)) {
			idMachine(newFile, x, lineNumb);
		}
		else if (x == '#') {
			int newLine = commentMachine(newFile, x, lineNumb);
			lineNumb = lineCheck(newLine, lineNumb);
		}
		else if (x == -1) {
			string newX = "";
			isEOF(newX, lineNumb);
		}
		else if ((isspace(x)) && (x != '\n')) {
			continue;
		}
		else {
			int check = unMachine(newFile, x, lineNumb);
			lineNumb = lineCheck(check, lineNumb);
		}
	}
};

bool Scanner::openFile(string fileName) {
	bool check = false;

	ifstream newFile(fileName);
	if (!newFile) {
		cout << "Error: Could not open the file. Make sure the name is correct." << endl;
	}
	else {
		scanFile(newFile);
		if (tokenCnt == 0) {
			string newX = "";
			int lineNum = 1;
			isEOF(newX, lineNum);
		}
	}

	return check;
};

int Scanner::getTokenCnt() {
	return tokenCnt;
};

void Scanner::print() {
	printTokes();
}

vector<Tokens> Scanner::getVec() {
	return newVec;
}
