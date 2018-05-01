#include "Database.h"



Database::Database()
{
}


Database::~Database(){
	newRow.clear();
	data.clear();
}

void Database::setCol(string name, vector<string> col) {
	//data.at(name)->setColumns(col);
}

void Database::addRow(string name, Tuple T) {
	data.at(name)->addRow(T);
}

void Database::addTable(string name, Relation *R) {
	data[name] = R;
}

void Database::toString(string name) {
	//data.at(name)->toString();
}

Relation* Database::selectID(string name, string newName, Scheme S) {
	Relation *R = data.at(name)->selectID(newName, S);
	return R;
}

Relation* Database::selectString(string name, string newName, string value, int index) {
	Relation *R = data.at(name)->selectString(newName, value, index);
	return R;
}

Relation* Database::selectStringTwo(string newName, string value, int index) {
	Relation *R = data.at(newName)->selectString(newName, value, index);
	return R;
}

Relation* Database::project(string name) {
	Relation *R = data.at(name)->project();
	return R;
}

Relation* Database::rename(string name) {
	Relation* R = data.at(name)->rename();
	return R;
}