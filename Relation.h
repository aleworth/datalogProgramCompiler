//#ifndef RELATION_H_
//#define RELATION_H_
#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include "Scheme.h"
#include "Tuple.h"


using namespace std;

class Relation
{
private:
	set<Tuple> rows;
	set<Tuple> newRows;
	set<Tuple> doubleRows;
	vector<Scheme> columns;
	vector<int> dblIndex;
	string name;
	int solutions;
	bool solution = false;
	bool doubleMarker = false;

	void doubleChecker(Scheme S);
	//Interpreter inter;
public:
	string getName();
	//void setRows(set<vector<string>> finalRows);
	//void setColumns(Scheme S);
	void addColumn(Scheme S);
	void addRow(Tuple T);
	void addSolution(int add);
	set<Tuple> getRows();
	Relation* selectString(string newName, string value, int index);
	Relation* selectIDDouble(int indexOne, int indexTwo, Relation* R);
	Relation* processID(Relation* R);
	Relation* selectID(string newName, Scheme S);
	Relation* project();
	void projectSort(vector<int> index);
	bool projectDouble(string check, vector<string> columns);
	Scheme projectScheme();
	void processRename(bool check, vector<string> columns);
	Relation* rename();
	bool columnCheck();
	/*void toString();
	set<vector<string>> selectID(string name, vector<string> query);
	set<vector<string>> selectString(string name, vector<string> query);
	void match(int index, vector<string> query);
	void evaluateRows(vector<string> tempRow, vector<string> query, int index);
	void matchTwo(int index, int firstMatch, vector<string> query);
	bool evaluateRowsTwo(vector<string> tempRow, vector<string> query, int index, int firstMatch);
	void matchID(int indexOne, int indexTwo);
	void evaluateID(vector<string> tempRow, int indexOne, int indexTwo);
	void noMatch();
	void clearSet();
	void project(vector<string> query);
	void rename(int index);
	void doubleID(int index);
	bool doubleChk(vector<string> query);
	void doubleTrouble();
    void projectTwo();*/
	Relation(string newName) {
		name = newName;
	};
	~Relation();
};

//#endif
