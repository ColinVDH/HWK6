#include <string>
#include <iostream>
using namespace std;
#include "Expression.h"



class ArithmeticExpression: public Expression {
private:

public:
	ArithmeticExpression(string leftstring, string rightstring, bool leaf);
	Expression* left;
	Expression* right;
	string leftstring;
	string rightstring;
	bool leaf;
	double evaluate();
	void print();
	float convert(string s);
};

