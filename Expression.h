/*
*Name: Junhao Wang, Colin Vandenhof, Teshaun Murray
*MacID: wangjh2, vandencm, murrayts
*Student Number: 1215428, 1231644, 1227515
*Description: expression class header.
*/

#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
#include <iostream>
using namespace std;

class Expression {
private:
public:
	virtual string evaluate(); //declare evaluate function-- evaluate expression and return string representation of the result.
	virtual void print(); // declare print function -- prints expression
};


#endif
