#include <string>
#include <iostream>
#include "Expression.h"
using namespace std;


Expression::Expression(): value(0){

}
Expression::Expression(int number): value(number){

}
virtual string Expression::evaluate(){

	// evaluate expression and return string representation of the result.
}
virtual void Expression::print(){

}

