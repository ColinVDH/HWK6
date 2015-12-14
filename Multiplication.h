/*
*Name: Junhao Wang, Colin Vandenhof, Teshaun Murray
*MacID: wangjh2, vandencm, murrayts
*Student Number: 1215428, 1231644, 1227515
*Description: multiplication class header.
*/
#include <string>
#include <iostream>
#include "ArithmeticExpression.h"
using namespace std;


//Multiplies two expression
class Multiplication: public ArithmeticExpression {
private:
public:
	Multiplication(string ls, string rs, string branch=""); //declare constructor, branch initialized to empty string by default.
	~Multiplication(); //declare destructor
	string evaluate(); //declare evaluate function
	void print();//declare print function

};
