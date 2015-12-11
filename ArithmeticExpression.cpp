#include <string>
#include <iostream>
#include <sstream>
#include "ArithmeticExpression.h"
using namespace std;

ArithmeticExpression::ArithmeticExpression(string ls, string rs, bool leaf) :
		leftstring(ls), rightstring(rs), leaf(false) {
	double d;
	char c;
	istringstream rss(rs);
	istringstream lss(ls);
	if (((rss >> d) && !(rss >> c)) && ((lss >> d) && !(lss >> c))) {
		leaf = true;
	}
}

double ArithmeticExpression::evaluate() {
	return 0.0;
}

void ArithmeticExpression::print() {
}

float ArithmeticExpression::convert(string s) {
	return 0.0;
}

