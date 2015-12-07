#include <string>
#include <iostream>
#include "ArithmeticExpression.h"
using namespace std;

//Divide two expression
class Division: public ArithmeticExpression {
private:
public:
	string evaluate();
	void print();
}
