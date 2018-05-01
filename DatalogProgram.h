#pragma once
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include "Tuple.h"
#include "Scheme.h"
#include "Relation.h"
#include "Database.h"

using namespace std;

class DatalogProgram
{
private:
	vector<string> schemes;
	int schemeCnt = 0;
	vector<string> facts;
	int factCnt = 0;
	vector<string> rules;
	int ruleCnt = 0;
	vector<string> queries;
	int queryCnt = 0;
	set<string> domains;
	int domainCnt = 0;
	Database D;
	vector<int> index;
	void indexSelector(Scheme S);
public:
	void addScheme(string scheme);
	void addFact(string fact);
	void addRule(string rule);
	void addQuery(string query);
	void addDomain(string domain);
	void toString();
	void processQueries();
	void evaluateSchemes(string scheme);
	void processSchemes();
	void evaluateFacts(string fact);
	void processFacts();
	void evaluateQueries(string query);
	void solutionMachine(bool stringChk, string name, string query, Tuple T, Scheme S);
	string getName(string query);
	Tuple getTuple(string query);
	Scheme getScheme(string query);
	bool getStrChk(string query);
	DatalogProgram();
	~DatalogProgram();
};

