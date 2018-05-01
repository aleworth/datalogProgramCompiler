#include <iostream>
#include <sstream>
#include <fstream>
#include "Scanner.h"
#include "Parser.h"
#include "Tokens.h"
#include "DatalogProgram.h"
//#include "Interpreter.h"

using namespace std;

int main(int argc, char* argv[1]) {
        string filename = argv[1];

        //string filename;
        //cout << "Please enter the name of the file you want to tokenize\n (Including the proper file extension.)" << endl;
        //cin >> filename;

	Scanner myScan = Scanner();
	myScan.openFile(filename);
        vector<Tokens> parsVec = myScan.getVec();

        Parser myPars = Parser(parsVec);
	try {
		myPars.dataParser();
	}
	catch (Tokens error) {
		cout << "Failure!\n";
		error.toString(error);
	}
	//Interpreter i;
	//i.relationToString();

	//myScan->print();
	//int tknCnt = myScan->getTokenCnt();
	//cout << "Total Tokens = " << tknCnt << endl;

    //system("pause");
	return 0;
}
