/*
*Name: Junhao Wang, Colin Vandenhof, Teshaun Murray
*MacID: wangjh2, vandencm, murrayts
*Student Number: 1215428, 1231644, 1227515
*Description: addition class definitions for constructor, destructor, print and evaluate.
*/
#include <sstream>
#include <stdlib.h>
#include "Addition.h"
using namespace std;

//Addition constructor.
Addition::Addition(string ls, string rs, string branch):
		ArithmeticExpression(ls, rs, branch){ //call parent class constructor
}
//Addition destructor
Addition::~Addition(){
	if (right) { //if the right object pointer is not NULL
		delete right; //delete the right object
	}
	if (left) { //if the left object pointer is not NULL
		delete left; //delete the left object
	}
}

//This function evaluates the expression in the current node.
string Addition::evaluate() {
	if (this->branch=="bothleaf") {//if the node branches to two numbers.
		return tostring(convert(leftstring.c_str())+convert(rightstring.c_str()));//return a string containing result of leftstring+rightstring
	}
	else if (this->branch=="rightleaf"){//if only the right branch is a number.
		return tostring(convert(left->evaluate())+convert(rightstring.c_str()));//return a string containing result of (left evaluate())+rightstring
	}
	else if (this->branch=="leftleaf"){//if only the left branch is a number.
		return tostring(convert(leftstring.c_str())+convert(right->evaluate()));//return a string containing result of leftstring+(right evaluate())
	}
	else return tostring(convert(left->evaluate())+convert(right->evaluate())); //if both direct branches are not numbers, return the string containing the result of left evaluate() + right evaluate()
}
//This function prints the expression as represented in the current node (and below).
void Addition::print() {
	if (this->branch=="bothleaf") { //if the node branches to two numbers.
		cout<<"("+leftstring+"+"+rightstring+")";//print a string that shows left number "+" right number, enclosed in brackets
	}
	else if (this->branch=="rightleaf") {//if only the right branches to a number.
		cout<< "("; left->print(); cout<<"+"+rightstring+")";//print opening bracket, call left print, print operator, right number, and closing bracket
	}
	else if (this->branch=="leftleaf") {//if only the left branches to a number.
		cout<<"("+leftstring+"+"; right->print(); cout<<")";//print opening bracket, left number and operator, call left print, print closing closing bracket
	}
	else {//if neither left nor right branches to a number
		cout<<"(";left->print();cout<<"+";right->print();cout<<")"; //print opening bracket, call left print(), print operator, call right print, print closing bracket
	}
}
