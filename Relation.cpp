#include "Relation.h"

Relation::~Relation() {

}

string Relation::getName() {
	return name;
}

void Relation::addRow(Tuple T) {
	if (doubleMarker) {
		doubleRows.insert(T);
	}
	else {
		rows.insert(T);
	}
}

set<Tuple> Relation::getRows() {
	return rows;
}

void Relation::addColumn(Scheme S) {
	columns.push_back(S);
}

void Relation::addSolution(int solution) {
	solutions += solution;
}

void Relation::doubleChecker(Scheme S) {
	vector<string> column = S.sendColumns();
	for (unsigned int i = 0; i < column.size(); i++) {
		int j = 0;
		if (i < column.size() - 1) {
			j = i + 1;
		}
		if (j == 0) {
			break;
		}
		else if (column.at(i) == column.at(j)) {
			dblIndex.push_back(i);
			dblIndex.push_back(j);
			doubleMarker = true;
		}
		else {
			;
		}
	}
}

Relation* Relation::selectString(string newName, string value, int index) {
	Relation *R = new Relation(newName);
	//doubleChecker(T);
		for (Tuple J : rows) {
			if (J.at(index) == value) {
				R->addRow(J);
			}
			else {
				;
			}
		}

	return R;
}

Relation* Relation::selectIDDouble(int indexOne, int indexTwo, Relation* R) {
	
	set<Tuple> doubleRows = R->getRows();
	Relation* K = new Relation(R->getName());
	for (Tuple J : doubleRows) {
		if (indexTwo == 0) {
			break;
		}
		else if (J.at(indexOne) == J.at(indexTwo)) {
			K->addRow(J);
			solution = true;
		}
		else {
			;
		}
	}

	return K;
}

Relation* Relation::processID(Relation* R) {
	for (unsigned int k = 0; k < dblIndex.size(); k++) {
		if (dblIndex.size() > 0) {
			unsigned int indexOne = dblIndex.at(0);
			dblIndex.erase(dblIndex.begin());
			unsigned int indexTwo = dblIndex.at(0);
			dblIndex.erase(dblIndex.begin());
			if (k > 0) {
				R = selectIDDouble(indexOne, indexTwo, R);
			}
			else {
				for (Tuple J : rows) {
					if (indexTwo == 0) {
						break;
					}
					else if (J.at(indexOne) == J.at(indexTwo)) {
						R->addRow(J);
						solution = true;
					}
					else {
						;
					}
				}
			}
		}
		else {
			;
		}
	}

	return R;
}

Relation* Relation::selectID(string newName, Scheme S) {
	Relation *R = new Relation(newName);
	doubleChecker(S);
	if (dblIndex.size() > 0) {
		R = processID(R);
	}
	else { //Use all rows in project.
		for (Tuple T : rows) {
			R->addRow(T);
		}
	}
	
	dblIndex.clear();
	return R;
}

bool Relation::projectDouble(string check, vector<string> columns) {
	for (unsigned int i = 0; i < columns.size(); i++) {
		if (check == columns.at(i)) {
			return true;
		}
		else {
			;
		}
	}

	return false;
}

Scheme Relation::projectScheme() {
	Scheme S;
	for (Scheme column : columns) {
		vector<string> columns = column.sendColumns();
		vector<string> newCol;
		for (unsigned int i = 0; i < columns.size(); i++) {
			string check = columns.at(i);
			if (check.at(0) == '\'') {
				;
			}
			else {
				bool checker = projectDouble(check, newCol);
				if (!checker) {
					newCol.push_back(check);
					S.addColumn(check);
				}
				else {
					;
				}
			}
		}
	}

	return S;
}

void Relation::projectSort(vector<int> index) {
	for (Tuple T : rows) {
		Tuple J;
		unsigned int counter = 0;
		unsigned int j = 0;
		for (unsigned int i = 0; i < T.size(); i++) {
			if (counter < index.size()) {
				j = index.at(counter);
			}
			if (i == j) {
				counter++;
			}
			else {
				string value = T.at(i);
				J.push_back(value);
			}
		}
		newRows.insert(J);
	}
	Scheme S = projectScheme();

	columns.clear();
	this->addColumn(S);
}

Relation* Relation::project() {
	Relation *R = new Relation(getName());
	vector<int> index;
	for (Scheme column : columns) {
		vector<string> columns = column.sendColumns();
		for (unsigned int i = 0; i < columns.size(); i++) {
			string check = columns.at(i);
			if (check.at(0) == '\'') {
				index.push_back(i);
			}
			else {
				;//do nothing; We only want the ones to get rid of.
			}
		}
	}
	if (index.size() == 0) {
		projectSort(index);
		/*if (rows.size() == 0) {
			R = this;
			return R;
		}*/
		R = this;
		return R;
	}
	else if (rows.size() == 0) {
		R = this;
		return R;
	}
	else {
		set<Tuple>::iterator iter = rows.begin();
		Tuple T = *iter;
		if (index.size() == T.size()) {
			R = this;
		}
		else {
			projectSort(index);
			rows.clear();
			rows = newRows;
			newRows.clear();
		}
	}
	return R;
}

bool Relation::columnCheck() {
	bool colCheck = false;
	vector<int> count;
	for (Scheme column : columns) {
		vector<string> columns = column.sendColumns();
		string check;
		for (unsigned int i = 0; i < columns.size(); i++) {
			check = columns.at(i);
			char checker = check.at(0);
			if (checker == '\'') {
				count.push_back(i);
			}
			else {
				;
			}
		}
		if (count.size() == columns.size()) {
			colCheck = true;
		}
		else {
			;
		}
	}

	return colCheck;
}

void Relation::processRename(bool check, vector<string> columns) {
	if (rows.size() > 0) {
		if (check) {
			cout << name << " Yes(" << rows.size() << ")" << endl;
		}
		else {
			cout << name << " Yes(" << rows.size() << ")" << endl;
			for (Tuple T : rows) {
				for (unsigned int i = 0; i < columns.size(); i++) {
					if (columns.size() == 1) {
						cout << "  " << columns.at(i) << "=" << T.at(i) << endl;
					}
					else if (i == columns.size() - 1) {
						cout << columns.at(i) << "=" << T.at(i) << endl;
					}
					else if (i == 0) {
						cout << "  " << columns.at(i) << "=" << T.at(i) << ", ";
					}
					else {
						cout << columns.at(i) << "=" << T.at(i) << ", ";
					}
				}
			}
		}
	}
	else {
		cout << name << " No" << endl;
	}
}

Relation* Relation::rename() {
	Relation* R = new Relation(getName());
	R = this;
	for (Scheme column : columns) {
		vector<string> columns = column.sendColumns();
		string name = getName();
		bool check = columnCheck();
		processRename(check, columns);
	}

	return R;
};

/*void Relation::toString() {
	cout << name << "\n";
        for (unsigned int i = 0; i < columns.size(); i++) {
		cout << columns.at(i) << "\n";
	}
        //set<vector<string>>::iterator itr = rows.begin();
        for (vector<string> tempRow : rows) {
                for (unsigned int i = 0; i < tempRow.size(); i++) {
			cout << tempRow.at(i) << endl;
		}
	}
}

void Relation::evaluateRows(vector<string> tempRow, vector<string> query, int index) {
	if (query.at(index) == tempRow.at(index)) {
		string row = tempRow.at(index);
		newRow = tempRow;
		//newRows.insert(newRow);
		solution = true;
	}
	else {
		;
	}
}

bool Relation::evaluateRowsTwo(vector<string> tempRow, vector<string> query, int index, int firstMatch) {
	if (query.at(index) == tempRow.at(index) && query.at(firstMatch) == tempRow.at(firstMatch)) {
		return true;
	}
	else {
		//remove vector from newRows
		return false;
	}
}

void Relation::match(int index, vector<string> query) {
        //set<vector<string>>::iterator itr = rows.begin();
        for (vector<string> tempRow : rows) {
		evaluateRows(tempRow, query, index);
	}
}

void Relation::matchTwo(int index, int firstMatch, vector<string> query) {
        for (vector<string> tempRow : rows) {
		bool check = false;
                //tempRow = *itr;
		check = evaluateRowsTwo(tempRow, query, index, firstMatch);
		if (check) {
			;
		}
		else {
                        newRows.erase(tempRow);
                        //tempRow = newRows.begin();
		}
	}
}

void Relation::evaluateID(vector<string> tempRow, int indexOne, int indexTwo) {
	if (tempRow.at(indexOne) == tempRow.at(indexTwo)) {
		newRows.insert(tempRow);
		solution = true;
	}
	else {
		;
	}
}

void Relation::matchID(int indexOne, int indexTwo) {
    for (vector<string> tempRow : rows) {
	evaluateID(tempRow, indexOne, indexTwo);
	}
}

void Relation::noMatch() {
	if (rows.size() > 0) {
		solution = true;
		for (vector<string> tempRow : rows) {
			newRows.insert(tempRow);
		}
	}
	else {
		;
	}
}

void Relation::doubleID(int index) {

}

bool Relation::doubleChk(vector<string> query) {
	bool goodies = false;
	
	if (query.size() == 1) {
		return false;
	}
	else {
                for (unsigned int j = 0; j < query.size(); j++) {
			string checker = query.at(j);
			indexes.push_back(j);
                        for (unsigned int i = 1; i < query.size(); i++) {
				if (checker == query.at(i)) {
					indexes.push_back(i);
					doubleTrouble();
					goodies = true;
					indexes.pop_back();
				}
				else {
					indexes.pop_back();
				}
			}
			if (indexes.size() > 0) {
				indexes.pop_back();
			}
			if (query.size() == 2) {
				break;
			}
			else {
				;
			}
		}
	}
	return goodies;
}

void Relation::doubleTrouble() {
		int j = indexes.at(0);
		int k = indexes.at(1);
		for (vector<string> tempRow : rows) {
			evaluateID(tempRow, j, k);
		}
}

set<vector<string>> Relation::selectID(string name, vector<string> query) {
	string receiver;
	string matcher;
        bool check = false;
	check = doubleChk(query);
	if (!check) {
		noMatch();
	}
	else {
		;
	}
	if (solution) {
		cout << name << " Yes(" << newRows.size() << ")" << endl;
	}
	else {
		cout << name << " No" << endl;
	}
	solution = false;
	return newRows;
}

set<vector<string>> Relation::selectString(string name, vector<string> query) {
	string receiver;
	int firstMatch;
        for (unsigned int i = 0; i < query.size(); i++) {
		receiver = query.at(i);
		if (receiver == columns.at(i)) {
			;
		}
		else if (receiver.at(0) != '\'') {
			;
		}
		else {
			if (newRows.size() > 1) {
				matchTwo(i, firstMatch, query);
			}
			else {
				match(i, query);
				if (newRows.size() < 1) {
                                        cout << name << " No" << endl;
					return newRows;
				}
				else {
					firstMatch = i;
				}
			}
		}
	}
	receiver = "";
        //strIndex = 0;
	if (solution) {
		cout << name << " Yes(" << newRows.size() << ")" << endl;
	}
	else {
		cout << name << " No" << endl;
	}
	solution = false;
	return newRows;
}

void Relation::setRows(set<vector<string>> finalRows) {
	rows = finalRows;
};

void Relation::clearSet() {
	newRows.clear();
}

void Relation::rename(int index) {
	if (newRows.size() == 0) {
		set<vector<string>>::iterator itr = rows.begin();
		advance(itr, index);
		tempRow = *itr;
	}
	else {
		set<vector<string>>::iterator itr = newRows.begin();
		advance(itr, index);
		tempRow = *itr;
	}
        unsigned int i = 0;
		while (i < columns.size()) {
				if (i == (columns.size() - 1) && i == 0) {
				cout << "  " << columns.at(i) << "=" << tempRow.at(i) << endl;
				i++;
				}
				else if (i == 0) {
					cout << "  " << columns.at(i) << "=" << tempRow.at(i) << ", ";
					i++;
				}
				else if (i == (columns.size() - 1)) {
					cout << columns.at(i) << "=" << tempRow.at(i) << endl;
					i++;
				}
				else {
					cout << columns.at(i) << "=" << tempRow.at(i) << ", ";
					i++;
				}
		}
}

void Relation::projectSort(vector<string> query) {
                for (unsigned int i = 0; i < query.size(); i++) {
			string value = query.at(i);
			string dblChk;
			if (i != query.size() - 1) {
				dblChk = query.at(i + 1);
			}
			else {
				;
			}
			char checker = '\'';
			if (checker == value.at(0)) {
                for (vector<string> tempRow : rows) {
					tempRow.erase(tempRow.begin() + i);
					newRows.insert(tempRow);
				}
			}
			else if (dblChk == value) {
				for (vector<string> tempRow : rows) {
					tempRow.erase(tempRow.begin() + i + 1);
					newRows.insert(tempRow);
				}
			}
			else {
				;
			}
		}
}

void Relation::projectTwo() {
    for (unsigned int i = 0; i < rows.size(); i++) {
            unsigned int j = i + 1;
            if (columns.size() == 1) {
                    rename(i);
            }
            else if (j >= columns.size()) {
                    rename(i);
            }
            else if (columns.at(i) == columns.at(j)) {
                    columns.erase(columns.begin() + j);
                    newRows = rows;
                    rename(i);
            }
            else {
                    rename(i);
            }
    }
}

void Relation::project(vector<string> query) {
	if (columns.size() == 0) {
		return;
	}
	else {
		projectSort(query);
		if (newRows.size() == 0) {
                        projectTwo();
		}
		else {
			for (unsigned int i = 0; i < newRows.size(); i++) {
				unsigned int j = i + 1;
				if (columns.size() == 1) {
					rename(i);
				}
				else if (j >= columns.size()) {
					rename(i);
				}
				else if (columns.at(i) == columns.at(j)) {
					columns.erase(columns.begin() + j);
					newRows = rows;
					rename(i);
				}
				else {
					rename(i);
				}
			}
		}
	}
}*/
