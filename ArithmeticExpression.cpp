#include <string>
#include <iostream>
#include "ArithmeticExpression.h"
using namespace std;

ArithmeticExpression::ArithmeticExpression(Expression *l, Expression *r, char op): left(l), right(r), op(op){
}
ArithmeticExpression::ArithmeticExpression(double value): number(value){
}
string ArithmeticExpression::evaluate(){
ostringstream stream;
switch (op){
case '+': stream<<Addition::evaluate();
	break;
case '-': stream<<Subtraction::evaluate();
	break;

case '*': stream<<Multiplication::evaluate();
	break;
case '/':stream<<Division::evaluate();
	break;
}
return stream.str();
}

void ArithmeticExpression::print(){
	cout<<ArithmeticExpression::evaluate();
}
float ArithmeticExpression::convert(string s){
	return stof(s);
}


