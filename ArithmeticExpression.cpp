/*
*Name: Junhao Wang, Colin Vandenhof, Teshaun Murray
*MacID: wangjh2, vandencm, murrayts
*Student Number: 1215428, 1231644, 1227515
*Description: arithmetic expression class definitions, including the constructor, destructor, print, evaluate, and helper functions: convert, tostring and isNumber.
*/
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "ArithmeticExpression.h"
using namespace std;


//ArithmeticExpression constructor
ArithmeticExpression::ArithmeticExpression(string ls, string rs, string branch) :
		leftstring(ls), rightstring(rs), branch("") { //initialize leftstring, rightstring and branch variables
	if (isNumber(leftstring.c_str()) && isNumber(rightstring.c_str())) { //if the leftstring and the rightstring are both numbers
		this->branch = "bothleaf"; //mark this node a bothleaf (points to two numbers)
	} else if (isNumber(rightstring.c_str())) { //if the rightstring is a number
		this->branch = "rightleaf"; //mark this node a rightleaf
	} else if (isNumber(leftstring.c_str())) {  //if the leftstring is a number
		this->branch = "leftleaf"; //mark this node a leftleaf
	}
}

//ArithmeticExpression destructor
ArithmeticExpression::~ArithmeticExpression(){
	if (right){ //if right pointer is initialized to something
		delete right; //delete the right object
	}
	if (left){ //if left pointer is initliazed to something
		delete left; //delete the left object.
	}
}
/*

//This function adds 1 to any leaf expressions
void ArithmeticExpression::increment() {
	if (branch=="leftleaf"){ //if it is a leftleaf
		leftstring=tostring(convert(leftstring)+1); //left is a number, so it gets incremented
		right->increment(); //call increment on the right node.
	}
	else if (branch=="rightleaf"){//if it is a rightleaf
		rightstring=tostring(convert(rightstring)+1);//right is a number, so it gets incremented
		left->increment();//call increment on the left node.
	}
	else if (branch=="bothleaf"){//if it is a bothleaf
		leftstring=tostring(convert(leftstring)+1); //left is a number, so it gets incremented
		rightstring=tostring(convert(rightstring)+1);//right is a number, so it gets incremented
	}
	else{ //if it branches to two child nodes (no numbers)
		left->increment();//call increment on the left node.
		right->increment();//call increment on the right node.
	}
}

*/

//This function evaluates the current node. Overridden by operator subclasses.
string ArithmeticExpression::evaluate(){
	return "-1";
}
//This function prints the current node. Overridden by operator subclasses.
void ArithmeticExpression::print(){
}

//This function converts a string to a float.
float ArithmeticExpression::convert(string s) {
	return atof(s.c_str()); //convert to c-string, then to a float.
}
//This function converts a float to a string.
string ArithmeticExpression::tostring(float f) {
	ostringstream ss; //make a stringstream object.
	ss << f; //stringstream makes float into a string
	return ss.str(); //returns string output.
}

//This function returns true if the input string is numeric.
bool ArithmeticExpression::isNumber(const char* str) {
	char* endptr = 0; //end pointer is initialized to 0
	strtod(str, &endptr);  //string to double function
	if (*endptr != '\0' || endptr == str) //if end pointer does not equal end character OR endpointer is set to the original string, this indicates the function has failed to convert.
		return false;//return that it is not a number
	return true; //else, it is a number.
}







