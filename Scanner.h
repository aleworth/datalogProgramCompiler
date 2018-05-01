#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Tokens.h"

using namespace std;

class Scanner {

private:
	vector<Tokens> newVec;
	void createToken(string type, string value, int lineNum);
	void printTokes();
	bool isEasy(char a, int lineNumb);
	string easyMachine(char a);
	string eMachAlpha(char a);
	string eMachBeta(char a);
	void isID(string value, int lineNumb);
	void idMachine(ifstream& newFile, char x, int lineNumb);
	void isString(string value, int lineNumb);
	int strMachine(ifstream& newFile, char x, int lineNumb);
	void isComment(string value, int lineNumb);
	int comBlock(ifstream& newFile, char x, int lineNumb);
	int commentMachine(ifstream& newFile, char x, int lineNumb);
	void isUn(string value, int lineNumb);
	int unMachine(ifstream& newFile, char x, int lineNumb);
	void isEOF(string x, int lineNumb);
	int lineCheck(int newLine, int oldLine);
public:
	int tokenCnt = 0;
	int getTokenCnt();
	void print();
	vector<Tokens> getVec();
	Scanner();
	~Scanner();

	bool openFile(string fileName);
	void scanFile(ifstream& newFile);
};
