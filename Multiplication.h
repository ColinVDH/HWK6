#include <string>
#include <iostream>
#include "ArithmeticExpression.h"
using namespace std;

//Multiply two expression
class Multiplication: public ArithmeticExpression {
private:
public:
	string evaluate();
	void print();
}
