#include "DatalogProgram.h"



DatalogProgram::DatalogProgram()
{
}


DatalogProgram::~DatalogProgram()
{
}

void DatalogProgram::addScheme(string scheme) {
	schemes.push_back(scheme);
	schemeCnt++;
}

void DatalogProgram::addFact(string fact) {
	facts.push_back(fact);
	factCnt++;
	//T.sorter(fact);
}

void DatalogProgram::addRule(string rule) {
	rules.push_back(rule);
	ruleCnt++;
}

void DatalogProgram::addQuery(string query) {
	queries.push_back(query);
	queryCnt++;
}

void DatalogProgram::addDomain(string domain) {
	domains.insert(domain);
	domainCnt++;
}

void DatalogProgram::toString() {
	cout << "Success!\n";
	cout << "Schemes(" << schemeCnt << "):\n";
        for (unsigned int i = 0; i < schemes.size(); i++) {
		string scheme = schemes.at(i);
		cout << "  " << scheme << endl;
		}
	cout << "Facts(" << factCnt << "):\n";
        for (unsigned int i = 0; i < facts.size(); i++) {
		string fact = facts.at(i);
		cout << "  " << fact << endl;
	}
	cout << "Rules(" << ruleCnt << "):\n";
        for (unsigned int i = 0; i < rules.size(); i++) {
		string rule = rules.at(i);
		cout << "  " << rule << endl;
	}
	cout << "Queries(" << queryCnt << "):\n";
        for (unsigned int i = 0; i < queries.size(); i++) {
		string query = queries.at(i);
		cout << "  " << query << endl;
	}
	cout << "Domain(" << domains.size() << "):\n";
	for (set<string>::iterator itr = domains.begin(); itr != domains.end(); itr++) {
		cout << "  " << *itr << endl;
	}
}

void DatalogProgram::evaluateSchemes(string scheme) {
	char selector;
	string name;
	string schemee;
	Relation *R = new Relation(name);
	Scheme S;
	bool check = false;
	for (unsigned int i = 0; i < scheme.size(); i++) {
		selector = scheme.at(i);
		if (selector == '(') {
			check = true;
			D.addTable(name, R);
		}
		else if (selector == ',' || selector == ')') {
			S.addColumn(schemee);
			schemee = "";
		}
		else if (check) {
			schemee += selector;
		}
		else if (!check) {
			name += selector;
		}
		else {
			;
		}
	}
	R->addColumn(S);
}

void DatalogProgram::processSchemes() {
	for (unsigned int i = 0; i < schemes.size(); i++) {
		string scheme = schemes.at(i);
		evaluateSchemes(scheme);
	}
}

void DatalogProgram::evaluateFacts(string fact) {
	char selector;
	string name;
	string tuple;
	Tuple T;
	bool check = false;
	for (unsigned int i = 0; i < fact.size(); i++) {
		selector = fact.at(i);
		if (selector == '(') {
			check = true;
		}
		else if (selector == ',' || selector == ')') {
			T.push_back(tuple);
			tuple = "";
		}
		else if (check) {
			tuple += selector;
		}
		else if (!check) {
			name += selector;
		}
		else {
			;
		}
	}
	D.addRow(name, T);
}

void DatalogProgram::processFacts() {
	for (unsigned int i = 0; i < facts.size(); i++) {
		string fact = facts.at(i);
		evaluateFacts(fact);
	}
}

void DatalogProgram::solutionMachine(bool stringChk, string name, string query, Tuple T, Scheme S) {
	if (stringChk) {
		int inex = index.at(0);
		Relation* R = D.selectString(name, query, T.at(0), inex);
		D.addTable(query, R);
		for (unsigned int i = 1; i < T.size(); i++) {
			int inex = index.at(i);
			R = D.selectStringTwo(query, T.at(i), inex);
			D.addTable(query, R);
		}
		D.addTable(query, R);
		R->addColumn(S);
		R = D.project(query);
		R = D.rename(query);
		D.addTable(query, R);
		index.clear();
	}
	else {
		Relation *R = D.selectID(name, query, S);
		D.addTable(query, R);
		R->addColumn(S);
		R = D.project(query);
		R = D.rename(query);
		D.addTable(query, R);
		index.clear();
	}
}

string DatalogProgram::getName(string query) {
	string name;
	int i = 0;
	char selector = query.at(i);
	while (selector != '(') {
		name += selector;
		i++;
		selector = query.at(i);
	 }
	return name;
}

Tuple DatalogProgram::getTuple(string query) {
	string tuple;
	char selector;
	Tuple T;
	bool stringChk = false;
	
	for (unsigned int i = 0; i < query.size(); i++) {
		selector = query.at(i);
		if (selector == '\'') {
			stringChk = true;
		}
		if ((selector == ',' || selector == ')') && (stringChk)) {
			T.push_back(tuple);
			tuple = "";
			stringChk = false;
		}
		else if (stringChk) {
			tuple += selector;
		}
		else {
			;
		}
	}

	return T;
}

Scheme DatalogProgram::getScheme(string query) {
	string schemee;
	char selector;
	bool check = false;
	Scheme S;

	for (unsigned int i = 0; i < query.size(); i++) {
		selector = query.at(i);
		if (selector == '(') {
			check = true;
		}
		else if (selector == ',' || selector == ')') {
			S.addColumn(schemee);
			schemee = "";
		}
		else if (check) {
			schemee += selector;
		}
		else {
			;
		}
	}

	return S;
}

bool DatalogProgram::getStrChk(string query) {
	char selector;
	bool stringCheck = false;
	
	for (unsigned int i = 0; i < query.size(); i++) {
		selector = query.at(i);
		if (selector == '\'') {
			stringCheck = true;
			return stringCheck;
		}
		else {
			;
		}
	}

	return stringCheck;
}

void DatalogProgram::indexSelector(Scheme S) {
	vector<string> column = S.sendColumns();
	for (unsigned int i = 0; i < column.size(); i++) {
		string check = column.at(i);
		char checker = check.at(0);
		if (checker == '\'') {
			index.push_back(i);
		}
		else {
			;
		}
	}
}

void DatalogProgram::evaluateQueries(string query) {
	string name;
	string tuple;
	string schemee = "";
	Tuple T;
	Scheme S;
	bool stringChk = false;

	name = getName(query);
	T = getTuple(query);
	S = getScheme(query);
	stringChk = getStrChk(query);
	indexSelector(S);
	solutionMachine(stringChk, name, query, T, S);
}

void DatalogProgram::processQueries() {
	processSchemes();
	processFacts();
	for (unsigned int i = 0; i < queries.size(); i++) {
		string query = queries.at(i);
		evaluateQueries(query);
	}
}
