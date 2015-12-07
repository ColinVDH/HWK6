#include <string>
#include <iostream>
#include "ArithmeticExpression.h"
using namespace std;

//Subtract two expression
class Subtraction: public ArithmeticExpression {
private:
public:
	string evaluate();
	void print();
}
