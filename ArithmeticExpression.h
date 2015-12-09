#include <string>
#include <iostream>
using namespace std;
#include "Expression.h"



class ArithmeticExpression: public Expression {
private:

public:
	Expression* left;
	Expression* right;
	bool leaf;
	virtual double evaluate();
	virtual void print();
	float convert(string s);
	ArithmeticExpression();
};

