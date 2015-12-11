#include <string>
#include <iostream>
#include <sstream>
#include "Addition.h"
using namespace std;

Addition::Addition(string ls, string rs, bool leaf): ArithmeticExpression(ls, rs, leaf){
}

double Addition::evaluate() {
if (leaf) return stod(leftstring)+stod(rightstring);
else return left->evaluate()+right->evaluate();
}
void Addition::print() {
std::cout << evaluate();
}
