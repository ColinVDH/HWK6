#include <string>
#include <iostream>
#include "Expression.h"
using namespace std;

class ArithmeticExpression: public Expression {
private:
public:
	Expression *left;
	Expression *right;
	string evaluate();
	void print();
	float convert(string s);
};

