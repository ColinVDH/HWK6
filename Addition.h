#include <string>
#include <iostream>
#include "ArithmeticExpression.h"
using namespace std;


//Add two expression
class Addition: public ArithmeticExpression {
private:

public:
	 string leftstring;
	 string rightstring;
	 bool leaf;
	Addition(string ls, string rs, bool leaf);
	virtual double evaluate();
	virtual void print();

};
