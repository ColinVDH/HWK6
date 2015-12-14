/*
*Name: Junhao Wang, Colin Vandenhof, Teshaun Murray
*MacID: wangjh2, vandencm, murrayts
*Student Number: 1215428, 1231644, 1227515
*Description: subtraction class header
*/

#include <string>
#include <iostream>
#include "ArithmeticExpression.h"
using namespace std;


//Subtracts two expression
class Subtraction: public ArithmeticExpression {
private:
public:
	Subtraction(string ls, string rs, string branch="");//declare constructor, branch initialized to empty string by default.
	~Subtraction(); //declare destructor
	string evaluate(); //declare evaluate function
	void print(); //declare print function

};
