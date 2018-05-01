#include "Scheme.h"



Scheme::Scheme()
{
}


Scheme::~Scheme()
{
}

void Scheme::addColumn(string scheme) {
	columns.push_back(scheme);
}

//Adds columns to the relation
vector<string> Scheme::sendColumns() { 
	return columns;
}

void Scheme::clearColumn() {
	columns.clear();
}

/*void Scheme::makeColumns(string name) {
	for (int i = 0; i < name.length(); i++) {
		stringstream columnMaster;
		columnMaster << name.at(i);
		string columnSlave;
		columnMaster >> columnSlave;
		addColumn(columnSlave);
	}
}*/