#include <iostream>
#include <string>
#include "Expression.cpp"
#include "ArithmeticExpression.cpp"
#include "Addition.cpp"
#include "Subtraction.cpp"
#include "Multiplication.cpp"
#include "Division.cpp"
using namespace std;

void parseinput(string user_input){






int main()
{
	string user_input;
	while (user_input!="#"){
	cout<<"Please enter an expression: "<<endl;
	cin>>user_input;
	parseinput(user_input);
	}
	return 0;
}
