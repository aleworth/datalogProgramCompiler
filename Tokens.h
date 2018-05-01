#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

class Tokens {
public:
	
	string type = "";
	string value = "";
	int lineNum = 0;
	void toString(Tokens failure);
	/*void addCharToMap(char value);
	void addKeyToMap(string value);
	void addIDToMap(string value);
	void addComToMap(string value);
	void addUnToMap(string value);
	void addEOFToMap(char x);*/

	Tokens(string newType, string newValue, int newLineNum) {
		type = newType;
		value = newValue;
		lineNum = newLineNum;
	};
	~Tokens();
};
