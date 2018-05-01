#pragma once
#include <vector>
#include <iostream>
#include <sstream>

#include "Scanner.h"
#include "Predicate.h"
#include "Parameter.h"
#include "DatalogProgram.h"

using namespace std;

class Parser
{
private:
	unsigned int tokenItr = 0;
	string terminal;
	vector<Tokens> parsVec;
	vector<string> schemes;
	Predicate pred;
	DatalogProgram data;

	void match(string terminal);
	void checkColon(Tokens currToken);
	bool checkComma();
	bool checkID();
	void newParam(string terminal);
	void idList();
	void headPredicate();
	void scheme();
	void schemeList();
	void stringList();
	void fact();
	void factList();
	void addColonDash(string terminal);
	string isOperator();
	string expParameter();
	string expression(string awesome);
	void parameter();
	void parameterList();
	void predicate();
	void predicateList();
	void rule();
	void ruleList();
	void query();
	void queryList();

public:
	void dataParser();
	Parser(vector<Tokens> newParsVec) {
		for (unsigned int i = 0; i < newParsVec.size(); i++) {
			parsVec.push_back(newParsVec.at(i));
		}
	};
	~Parser();
};

