#include <string>
#include <iostream>
#include "ArithmeticExpression.h"
using namespace std;


//Add two expression
class Addition: public ArithmeticExpression {
private:

public:
	Addition(string ls, string rs, bool leaf);
	double evaluate();
	void print();

};
