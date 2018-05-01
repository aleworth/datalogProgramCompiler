#include "Parser.h"


Parser::~Parser()
{
}

void Parser::match(string terminal) {
	if (parsVec.at(tokenItr).type == terminal) {
		tokenItr++;
	}
	else {
		throw(parsVec.at(tokenItr));
	}
};

void Parser::checkColon(Tokens currToken) {
	if (currToken.type == "COLON") {
		tokenItr++;
	}
	else {
		throw(currToken);
	}
};

bool Parser::checkComma() {
	if (parsVec.at(tokenItr).type == "COMMA") {
		return true;
	}
	else {
		return false;
	}
};

bool Parser::checkID() {
	if (tokenItr >= parsVec.size()) {
		return false;
	}
	if (parsVec.at(tokenItr).type == "ID") {
		return true;
	}
	else {
		return false;
	}

};

void Parser::newParam(string terminal) {
	string val = parsVec.at(tokenItr).value;
	match(terminal); 
	pred.addParam(val);
}

void Parser::idList() {
	if (checkComma()) {
		terminal = "COMMA"; newParam(terminal);
		terminal = "ID";
			newParam(terminal);
	}
	else {
		return;
	}
	idList();
};

void Parser::headPredicate() {
	terminal = "LEFT_PAREN"; newParam(terminal);
	terminal = "ID";
		newParam(terminal);
	idList();
	terminal = "RIGHT_PAREN"; newParam(terminal);
};

void Parser::scheme() {
	terminal = "ID";
		pred.schemeName(parsVec.at(tokenItr).value);
		match(terminal);
	headPredicate();
	pred.createScheme();
}

void Parser::schemeList() {
	if (checkID()) {
		scheme();
		schemeList();
	}
	else {
		return;
	}
};

void Parser::stringList() {
	if (checkComma()) {
		terminal = "COMMA"; match(terminal);
		terminal = "STRING"; 
			pred.addDomain(parsVec.at(tokenItr).value);
			newParam(terminal);
		stringList();
	}
	else {
		return;
	}
}

void Parser::fact() {
	terminal = "ID";
	if (parsVec.at(tokenItr).type == "RULES") {
		return;
		}
		pred.factName(parsVec.at(tokenItr).value);
		match(terminal);
	terminal = "LEFT_PAREN"; match(terminal);
	terminal = "STRING";
		pred.addDomain(parsVec.at(tokenItr).value);
		newParam(terminal); 
	stringList();
	terminal = "RIGHT_PAREN"; match(terminal);
	terminal = "PERIOD"; newParam(terminal);
	pred.createFact();
}

void Parser::factList() {
	if (parsVec.at(tokenItr).type == "RULES") {
		return;
	}
	else if (checkID()) {
		fact();
		factList();
	}
	else {
		return;
	}
};

void Parser::addColonDash(string terminal) {
	string val = parsVec.at(tokenItr).value;
	match(terminal);
	//Predicate pred;
	pred.addColonDash(val);
}

string Parser::isOperator() {
	string currOperator = parsVec.at(tokenItr).value;
	if (currOperator == "+") {
		terminal = "ADD";
		match(terminal);
		return currOperator;
	}
	else if (currOperator == "*") {
		terminal = "MULTIPLY";
		match(terminal);
		return currOperator;
	}
	else {
		terminal = "ERROR";
		match(terminal);
		return "error";
	}
}

string Parser::expParameter() {
	string currToken = parsVec.at(tokenItr).type;
	terminal = parsVec.at(tokenItr).type;
	if (currToken == "STRING") {
		currToken = parsVec.at(tokenItr).value;
		match(terminal);
		return currToken;
	}
	else if (currToken == "ID") {
		currToken = parsVec.at(tokenItr).value;
		match(terminal);
		return currToken;
	}
	else {
		string nest = "nested";
		return nest;
	}
}

string Parser::expression(string awesome) {
	
	string result;
	terminal = "LEFT_PAREN"; match(terminal); awesome += "(";
		result = expParameter();
			if (result == "nested") {
				awesome = (expression(awesome));
			}
			else {
				awesome += result;
			}
		result = isOperator();
			awesome += result;
		result = expParameter();
			if (result == "nested") {
				awesome = expression(awesome);
			}
			else {
				awesome += result;
			}
		terminal = "RIGHT_PAREN"; match(terminal); awesome += ")";
                result = awesome;

		return result;
}

void Parser::parameter() {
	string currToken = parsVec.at(tokenItr).type;
	if (currToken == "STRING") {
		newParam(currToken);
	}
	else if (currToken == "ID") {
		newParam(currToken);
	}
	else {
		string param = "expression";
		//Predicate pred;
		pred.addParam(param);
        string awesome;//possibly expression
		awesome = expression(awesome);
		pred.addExpression(awesome);
	}
}

void Parser::parameterList() {
	if (checkComma()) {
		terminal = "COMMA"; newParam(terminal);
			parameter();
			parameterList();
	}
	else {
		return;
	}
}

void Parser::predicate() {
	terminal = "ID";
		//Predicate pred;
		pred.predName(parsVec.at(tokenItr).value);
		newParam(terminal);
	terminal = "LEFT_PAREN"; newParam(terminal);
		parameter();
		parameterList();
	terminal = "RIGHT_PAREN"; newParam(terminal);
}

void Parser::predicateList() {
	if (checkComma()) {
		terminal = "COMMA"; newParam(terminal);
		predicate();
		predicateList();
	}
	else {
		return;
	}
}

void Parser::rule() {
	terminal = "ID";
		//Predicate pred;
		if (parsVec.at(tokenItr).type == "QUERIES") {
			return;
		}
		pred.ruleName(parsVec.at(tokenItr).value);
		match(terminal);
	headPredicate();
	terminal = "COLON_DASH"; addColonDash(terminal);
		predicate();
		predicateList();
	terminal = "PERIOD"; newParam(terminal);
	pred.createRule();
}

void Parser::ruleList() {
	if (parsVec.at(tokenItr).type == "QUERIES") {
		return;
	}
	else if (checkID()) {
		rule();
		ruleList();
	}
	else {
		return;
	}
}

void Parser::query() {
	predicate();
	if (parsVec.at(tokenItr).type == "EOF") {
		string val = "?";
		pred.addParam(val);
		pred.createQuery();
		return;
	}
	terminal = "Q_MARK"; newParam(terminal);
		//Predicate pred;
		pred.createQuery();
}

void Parser::queryList() {
	if (checkID()) {
		query();
		queryList();
	}
	else {
		return;
	}
}

void Parser::dataParser() {
	while (tokenItr != parsVec.size()) {
		if (parsVec.at(tokenItr).type == "EOF") {
			tokenItr++;
			continue;
		}
		terminal = "SCHEMES";
		match(terminal);
		checkColon(parsVec.at(tokenItr));
		scheme();
		schemeList();
		terminal = "FACTS";
		match(terminal);
		checkColon(parsVec.at(tokenItr));
		fact();
		factList();
		terminal = "RULES";
		match(terminal);
		checkColon(parsVec.at(tokenItr));
		rule();
		ruleList();
		terminal = "QUERIES";
		match(terminal);
		checkColon(parsVec.at(tokenItr));
		query();
		queryList();
	}
	pred.toString();
};

