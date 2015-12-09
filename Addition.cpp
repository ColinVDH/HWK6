#include <string>
#include <iostream>
#include <sstream>
#include "Addition.h"
using namespace std;

Addition::Addition(string ls, string rs, bool leaf) :
		leftstring(ls), rightstring(rs), leaf(false) {
	double d;
	char c;
	istringstream rss(rs);
	istringstream lss(ls);
	if (((rss >> d) && !(rss >> c)) && ((lss >> d) && !(lss >> c))){
		leaf=true;
	}
}

double Addition::evaluate() {
double leftnode = left->evaluate();
double rightnode = right->evaluate();
return leftnode + rightnode;
}
void Addition::print() {
std::cout << evaluate();
}
