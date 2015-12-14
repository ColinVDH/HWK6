/*
*Name: Junhao Wang, Colin Vandenhof, Teshaun Murray
*MacID: wangjh2, vandencm, murrayts
*Student Number: 1215428, 1231644, 1227515
*Description: arithmetic expression class header.
*/
#ifndef ARITHMETICEXPRESSION_H
#define ARITHMETICEXPRESSION_H
#include <string>
#include <iostream>
using namespace std;
#include "Expression.h"



class ArithmeticExpression: public Expression {
private:

public:
	ArithmeticExpression(string leftstring, string rightstring, string branch=""); //declare constructor, branch initialized to empty string by default.
	virtual ~ArithmeticExpression(); //declare destructor
	ArithmeticExpression* left=NULL; //left pointer initialized to NULL
	ArithmeticExpression* right=NULL;//right pointer initialized to NULL
	string leftstring;  //declare leftstring
	string rightstring;//declare rightstring
	string branch; //declare branch -- informs whether the node branches to other nodes, or is leaf
	bool isNumber(const char* str); //declare isNumber- checks if the string is numeric
	string evaluate(); //declare evaluate function
	void print();//declare print function
	float convert(string s); //declare convert function --string to float converter
	string tostring(float f); //declare tostring -- float to string converter
//	void increment(); //declare increment -- used to increment all numbers in the tree.
};

#endif
