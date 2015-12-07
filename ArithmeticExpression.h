#include <string>
#include <iostream>
#include "Expression.h"
using namespace std;

class ArithmeticExpression: public Expression {
private:
public:

	double number;
	char op;
	Expression *left;
	Expression *right;
	string evaluate();
	void print();
	float convert(string s);
	ArithmeticExpression(Expression *l, Expression *r, char op);
	ArithmeticExpression(double value);
};

