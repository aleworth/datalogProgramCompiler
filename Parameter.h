#pragma once
#include <iostream>

using namespace std;

class Parameter
{
public:
	string param;
	void toString();

	Parameter(string newParam) {
		param = newParam;
	};
	~Parameter();
};

