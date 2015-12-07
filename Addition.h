#include <string>
#include <iostream>
#include "ArithmeticExpression.h"
using namespace std;

//Add two expression
class Addition: public ArithmeticExpression {
private:
public:
	string evaluate();
	void print();

}
