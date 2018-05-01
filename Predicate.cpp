#include "Predicate.h"



Predicate::Predicate() {
}


Predicate::~Predicate()
{
}

void Predicate::addParam(string newParam) {
	Parameter param = Parameter(newParam);
	parameters.push_back(param);
};

void Predicate::schemeName(string newName) {
	sName = newName;
}

void Predicate::createScheme() {
	stringstream pred;

	pred << sName;
	//pred << "(";
        for (unsigned int i = 0; i < parameters.size(); i++) {
		if (i == parameters.size() - 1) {
			pred << parameters.at(i).param;
			//pred << ")";
		}
		else {
			pred << parameters.at(i).param;
			if ((parameters.at(i).param != ",") && (parameters.at(i).param != "(")) {
				;
			}
			else {
				;
			}
			//pred << ",";
		}
	};
	data.addScheme(pred.str());
	pred.clear();
	parameters.clear();
}

void Predicate::factName(string newName) {
	fName = newName;
}

void Predicate::createFact() {
	stringstream pred;

	pred << fName;
	pred << "(";
        for (unsigned int i = 0; i < parameters.size(); i++) {
		string check = parameters.at(i).param;
		if (check == ".") {
			pred << ")";
			pred << parameters.at(i).param;
		}
		else if (i == parameters.size() - 2) {
			pred << parameters.at(i).param;
		}
		else {
			pred << parameters.at(i).param;
			pred << ",";
		}
	};
	data.addFact(pred.str());
	pred.clear();
	parameters.clear();
}

void Predicate::addColonDash(string colonDash) {
	Parameter param = Parameter(colonDash);
	parameters.push_back(param);
}

void Predicate::addExpression(string expr) {
	expressions.push_back(expr);
}

void Predicate::predName(string newName) {
	predNames.push_back(newName);
}

void Predicate::ruleName(string newName) {
	rName = newName;
}

void Predicate::createRule() {
	stringstream pred;

	pred << rName;
        for (unsigned int i = 0; i < parameters.size(); i++) {
		Parameter expressionCheck = parameters.at(i);
		if (expressionCheck.param == "expression") {
			pred << expressions.at(expressionCnt);
			expressionCnt++;
		}
		else if (expressionCheck.param == ":-") {
			pred << " ";
			pred << parameters.at(i).param;
			pred << " ";
		}
		else {
			pred << parameters.at(i).param;
		}
	};
	data.addRule(pred.str());
	pred.clear();
	parameters.clear();
}

void Predicate::createQuery() {
	stringstream pred;

	//pred << rName;
        for (unsigned int i = 0; i < parameters.size(); i++) {
		Parameter expressionCheck = parameters.at(i);
		if (expressionCheck.param == "expression") {
			pred << expressions.at(expressionCnt);
			expressionCnt++;
		}
		else if (expressionCheck.param == ":-") {
			pred << " ";
			pred << parameters.at(i).param;
			pred << " ";
		}
		else {
			pred << parameters.at(i).param;
		}
	};
	data.addQuery(pred.str());
	pred.clear();
	parameters.clear();
}

void Predicate::toString() {
	data.processQueries();
}

void Predicate::addDomain(string domain) {
	data.addDomain(domain);
}
