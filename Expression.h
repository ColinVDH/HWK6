#include <string>
#include <iostream>
using namespace std;

class Expression {
private:

public:
	string leftstring;
	string rightstring;
	bool leaf;
	Expression* left;
	Expression* right;
	static Expression parse(string S);
	virtual double evaluate(); // evaluate expression and return string representation of the result.
	virtual void print(); // prints expression
	Expression();
};
