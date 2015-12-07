#include <string>
#include <iostream>
using namespace std;

class Expression {
private:
public:

	virtual string evaluate(); // evaluate expression and return string representation of the result.
	virtual void print(); // prints expression

};
