//#ifndef SCHEME_H_
//#define SCHEME_H_
#pragma once
#include <vector>
#include <sstream>

using namespace std;

class Scheme
{
private:
	vector<string> columns;
public:
	void addColumn(string scheme);
	vector<string> sendColumns();
	void clearColumn();
	//void makeColumns(string name);
	Scheme();
	~Scheme();
};

//#endif