/*
*Name: Junhao Wang, Colin Vandenhof, Teshaun Murray
*MacID: wangjh2, vandencm, murrayts
*Student Number: 1215428, 1231644, 1227515
*Description: contains main method, and helper functions needed to validate the expression, parse the expression, and create the tree.
*/

#include <sstream>
#include <stdlib.h>
#include <iomanip>
#include "Addition.h"
#include "Subtraction.h"
#include "Multiplication.h"
#include "Division.h"
using namespace std;

char brackets[] = { '(', ')','\0' }; //array to store brackets
char ops[] = { '*', '/', '-', '+','\0' }; //array to store operators
char digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9','\0' }; //array to store digits


//This function trims all whitespace from the string expression
void form(string &str) {
	string trimmed; //declare new string
	for (int i = 0; i < str.length(); i++) {//increments along the input string
		if (!(isspace(str[i]))) //if the character is not a whitespace...
			trimmed += str[i];  //add to the new string
	}
	str = trimmed; //assign string with whitespace removed to the input string.
}

//This function returns order of BEDMAS (0 if * or /, 1 if + or -)
int BEDMAS(char c) {
	for (int i = 0; i < 4; i++) { //4 operators, increment along
		if (c == ops[i]) return i / 2; //if the character is an operator, return its index/2 (0 if * or /, 1 if + or -).
	}
	return -1; // not an operator
}

//This function checks to see if a character is in a given array
bool check(const char a[], char c) {
	int i = 0;// index variable
	while (!(a[i]=='\0')){//while the array has not ended
	    if (a[i] == c){//if character was found
	        return true;//then it is in the array
	    }
	    i++;//index increase
	}
	return false;//not found, not in the array
}

//This function returns the index at which all opened brackets have closed.
int brackClose(string S) {
	int stack = 0;//bracket stack counter
	for (int i = 0; i < S.length(); i++) {//iterates through the characters
		if (S[i] == '(')//open bracket
			stack += 1; //Bracket level increased
		if (S[i] == ')')//close bracket
			stack -= 1; //Bracket level decreased
		if (stack == 0)//entire stack of brackets cleared
			return i; //returns the index at which the entire bracket stack was cleared
	}
	return -1; //something bad happened
}

//This function strips away the outer brackets of an expression, i.e. ((((((3+4)))))) becomes 3+4
void strip(string &S) {
	while ((S[0] == '(') && (brackClose(S) == (S.length() - 1))) {//while there are still outer brackets left
		int new_len = (S.length() - 2);//remove first and last character
		S = S.substr(1, new_len); //inclusive
	}
}

bool isNumber(const char* str) {
	char* endptr = 0; //end pointer is initialized to 0
	strtod(str, &endptr);  //string to double function
	if (*endptr != '\0' || endptr == str) //if end pointer does not equal end character OR endpointer is set to the original string, this indicates the function has failed to convert.
		return false;//return that it is not a number
	return true; //else, it is a number.
}

//This function checks if this expression contains valid characters and begins and ends with a number (- sign exception for beginning)
bool validForm(string S){
	if ((S[0]=='(')&&(S[S.length()-1]==')')&&(brackClose(S))){
		strip(S);
		if (isNumber(S.c_str())) return true;
	}

	strip(S);//removes excess brackets
    int br = 0;//bracket stack counter

    string number;
    for (int i = 0; i < S.length(); i++){//iterates through characters
        if((!check(ops,S[i])) && (!check(digit,S[i])) && (!check(brackets,S[i])) && (!(S[i]==' '))){//see if the character is within valid character sets
            return false;//if a non valid character was found, expression is bad
        }

        if (S[i] == '('){//if open bracket
            br++;//bracket level increase
        }else if (S[i] == ')'){//if close bracket
            br--;//bracket level decrease
        }
        if (br < 0){//bracket level should not go below 0
        	return false;//if so, then the expression is an invalid one
        }
    }
    if (!(br == 0 )){//if bracket stack is not 0 at the end of the expression
        return false;//invalid expression
    }

    //First Character checks:
    if ((S[0] == '+') || (S[0] == '*') || (S[0] == '/') || (S[0] == '-') ){//if first character is an operator
        return false;//invalid expression
    }

    //Last Character Check:
    if ((S[S.length()-1] == '-') || (S[S.length()-1] == '+') || (S[S.length()-1] == '*') || (S[S.length()-1] == '/')){//last character is an operator of any kind
        return false;//invalid expression
    }
    return true;//all tests passed, valid expression
}
//This function checks the expression for operator number coherency
bool expCheck(string S){
    strip(S);
    bool O = false;//flag for operator encountered
    bool N = false;//flag for number encountered
    bool Sp = false; //flag for space encountered
    bool carry = true;//boolean for recursion
    for (int i = 0; i < S.length(); i++){//iterates through characters
        //if an operator is encountered
        if (check(ops,S[i])){
        	//and a previous operator was encountered with no numbers in between
            if (O){
                return false;//this is a expression is not valid
            }
            //if an operator is encountered, turn the encountered number flag off, as there is now an operator between
            //it and the next number.
            N = false;
		//operator was encountered, turn operator flag on
            O = true;
            Sp = false;//if previous tests passed, we dont care about the last encountered space anymore
        }
        //if a digit was encountered
        else if(check(digit,S[i])){
		//last encountered a digit with a space between it and this digit
            if (N && Sp){
                return false; //this expression is invalid
            }
            if (O){//if an operator was encountered
                O = false;//there is now a number between this operator and whatever comes next, so operator flag is off
            }
            N = true;//we encountered a number
            Sp = false;//we dont care about spaces if all previous tests were passed
        }
        //encountered a bracket,treat bracket set and its content as a number for validity checking
        else if(check(brackets,S[i])){
		//if a number was previously encountered with no operator in between
            if (N){
                //this expression is invalid (implicit multiplication is not enforced in this program)
                return false;
            }
            if (O){//if operator was encountered
                O = false;//operator now has a numeric value following it, flag turned off
            }
            N = true;//numeric value encountered
            Sp = false;//dont care about spaces anymore

            string sub = S.substr(i);//creates a substring from current position to end

            int end = brackClose(sub);//calculates the distance to the bracket that closes the entire stack contained within
            sub = S.substr(i, end+1);//creates a substring with the content of the bracket

            carry = validForm(sub) && expCheck(sub);//checks contents of the bracket as if it was an expression on its own
            if (!carry){//if tests returns false
                return false;//invalid expression
            }
            i = end+i;//forwards the index to beyond the end of the closing bracket
        }else{//must be space encountered
            Sp = true;//space flag on
        }
    }
    return true;//all tests passed, valid expression
}

//This function parses the expression S into a left string (ls), operator (op), and right string (rs)
void parse(string &S, string &ls, char &op, string &rs) {
	form(S); //trim whitespace
	strip(S); //strip all outside brackets.
	int opIndex = 0; //Index of the first highest order OP
	int bLevel = 0; //we're only interested in operators OUTSIDE of brackets
	//loop through characters
	for (int i = (S.length()-1); i > -1; i--) { //decrement from end of expression
		if (S[i] == ')') //if closing bracket encountered...
			bLevel += 1; //Bracket level increased
		if (S[i] == '(')//if opening bracket encountered...
			bLevel -= 1; //Bracket level decreased
		//look for OPs
		if ((bLevel == 0) && check(ops, S[i])) {//outside of brackets and found an operator
			if (BEDMAS(S[i]) > BEDMAS(S[opIndex])) { //if the new operator is of higher order
				opIndex = i; //index of the operator
			}
		}
	}

	ls = S.substr(0, opIndex);//left side is everything left of the opindex
	rs = S.substr(opIndex + 1, S.length() - (opIndex + 1));//right side is everything right of the opIndex
	strip(ls); //strip all outside brackets from leftstring
	strip(rs);//strip all outside brackets from rightstring
	op = S[opIndex]; //operator is the character at opIndex.
}
//This function makes the root node.
ArithmeticExpression* makeRoot(string &user_input) {
	string ls(""), rs("");char op('0');//Initialize left and right string to empty. Arbitrarily initialize operator character.
	parse(user_input, ls, op, rs);      //parse initial expression
	ArithmeticExpression* root= NULL; //root pointer is set to NULL.
	switch (op) {  //switch on the operator
	        case '+': root = new Addition(ls, rs); //if "+", assign the root to a new addition object.
	        	break;
	        case '-': root = new Subtraction(ls, rs); //if "-", assign the root to a new subtraction object.
	        	break;
	        case '*': root= new Multiplication(ls,rs);//if "*", assign the root to a new multiplication object.
	        	break;
	        case '/': root= new Division(ls,rs);//if "/", assign the root to a new division object.
	        	        	break;
	    }
	return root; //return the root pointer.
}
//This function recursively builds the Expression tree.
void makeTree(ArithmeticExpression* &ParentExpression, bool left) {
	string ls(""), rs(""); char op('0'); //Initialize left and right string to empty. Arbitrarily initialize operator character.
	if (ParentExpression->branch == "bothleaf") { //if the expression only branches to leaf nodes...
		return; //no more child nodes to make, so return.
	} else {
		if (left) {  //if we are building the left child node
				if (ParentExpression->branch=="leftleaf") { //if it is a leaf...
					return; //no more child nodes to make
				}
				else parse(ParentExpression->leftstring, ls, op, rs); //else, make the left child node
		} else { //we are building the right child node
				if (ParentExpression->branch=="rightleaf") { //if it is a leaf...
					return;//no more child nodes to make
				}
				else parse(ParentExpression->rightstring, ls, op, rs); //else, make the right child node
			}
	}
	ArithmeticExpression *Child=NULL; //initialize child pointer to NULL
	switch (op) { //switch on operator
		case '+': Child = new Addition(ls, rs);//if "+", assign the child node to a new addition object.
			break;
		case '-': Child = new Subtraction(ls, rs);//if "-", assign the child node to a new subtraction object.
			break;
		case '*': Child = new Multiplication(ls, rs);//if "*", assign the child node to a new multiplication object.
			break;
		case '/': Child = new Division(ls, rs);//if "/", assign the child node to a new division object.
			break;
	}
	if (left) { //if we are building the left child node
		ParentExpression->left = Child; //the "left" pointer of the parent points to the child
	}
	else { //we are building the right child node
		ParentExpression->right = Child; //the "right" pointer of the parent points to the child
	}

	makeTree(Child, true);  //recursively call the function, with child now as the parent expression, to build its left child.
	makeTree(Child, false); //recursively call the function, with child now as the parent expression, to build its right child.
}


//MAIN function
int main() {
string user_input; //declare string for user input
ArithmeticExpression* root = NULL; //initialize root to NULL
while (user_input != "#") { //while the input is not #

	/*
if (user_input=="@"){ //if the input is "@"
		if (root!=NULL){ //if a valid expression can be incremented
			root->increment(); //increment all leaves in the tree recursively.
			root->print(); //print the function recursively, starting with the root.
			cout <<" = "<< setprecision(2) << fixed << atof((root->evaluate()).c_str())<<endl; //prints the answer as a float to two decimal places.
		}
		else cout << "No expression to increment"<<endl; //if root hasn't been made, print message.
	}
*/

if (!user_input.empty()){ // if user input has been initialized...
	if (expCheck(user_input)&&validForm(user_input)){ //if the input expression is valid...
		delete root;
		ArithmeticExpression* root = makeRoot(user_input); //make the root
		makeTree(root, true); //make left branch of tree
		makeTree(root, false); //make right branch of tree
		root->print(); //print the function recursively, starting with the root.
		cout <<" = "<< setprecision(2) << fixed << atof((root->evaluate()).c_str())<<endl; //prints the answer as a float to two decimal places.
	}
	else cout << "Expression is not well formed"<<endl; //if input expression is not valid, print message.
}

cout << "Please enter an expression: "; //ask user for input.
getline(cin, user_input); //input line goes into the user_input string.
}
delete root; //delete current tree
return 0;  //end of main.
}

