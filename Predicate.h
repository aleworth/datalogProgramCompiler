#ifndef PREDICATE_H_
#define PREDICATE_H_
#include <vector>
#include <iostream>
#include <sstream>
#include "Parameter.h"
#include "DatalogProgram.h"

using namespace std;

class Predicate
{
private:
	vector<Parameter> parameters;
	vector<string> predNames;
	vector<string> expressions;
	vector<string> domains;
	int expressionCnt = 0;
	int predNamesCnt = 0;
	string sName;
	string fName;
	string rName;
	DatalogProgram data;
public:
	void addParam(string newParam);
	void schemeName(string newName);
	void createScheme();
	void factName(string newName);
	void createFact();
	void addColonDash(string colonDash);
	void addExpression(string expr);
	void predName(string newName);
	void ruleName(string newName);
	void createRule();
	void createQuery();
	void toString();
	void addDomain(string domain);
	Predicate();
	~Predicate();
};

#endif
