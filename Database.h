//#ifndef DATABASE_H_
//#define DATABASE_H_
#pragma once
#include <map>
#include "Relation.h"
#include "Tuple.h"

using namespace std;

class Database
{
private:
	map<string, class Relation*> data;
	bool solution = false;
	set<vector<string>> newRow;
public:
	void setCol(string name, vector<string> col);
	void addRow(string name, Tuple);
	void addTable(string name, Relation *R);
	void toString(string name);
	Relation* selectID(string name, string newName, Scheme S);
	Relation* selectString(string name, string newName, string value, int index);
	Relation* selectStringTwo(string newName, string value, int index);
	Relation* project(string name);
	Relation* rename(string name);
	Database();
	~Database();
};

//#endif