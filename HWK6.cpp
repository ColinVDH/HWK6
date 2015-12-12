#include <iostream>
#include <string>
#include <sstream>
#include "Addition.h"
using namespace std;


char brackets[] = { '(', ')','\0' };
char ops[] = { '-', '+', '*', '/','\0' };
char digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' ,'\0'};

void form(string &str) {
	stringstream trimmer;
	trimmer << str;
	str.clear();
	trimmer >> str;
}

int BEDMAS(char c) { //returns order of BEDMAS (1 if * or /, 0 if + or -
	for (int i = 0; i < 4; i++) { //4 operators
		if (c == ops[i])//if ops match
			return i / 2;//integer division group ops into tiers with 2 on each tier based on order
	}
	return -1; // not an operator
}

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

int brackClose(string S) {
	int stack = 0;//bracket stack counter
	for (int i = 0; i < S.length(); i++) {//iterates through the characters
		if (S[i] == '(')//open bracket
			stack += 1; //Bracket level increased
		if (S[i] == ')') {//close bracket
			stack -= 1; //Bracket level decreased
			if (stack == 0)//entire stack of brackets cleared
				return i; //returns the index at which the entire bracket stack was cleared
		}
	}
	return -1; //something bad happened
}

//This function strips away the outer brackets of an expression, i.e. ((((((3+4)))))) becomes 3+4
string strip(string S) {
	while ((S[0] == '(') && (brackClose(S) == S.length() - 1)) {//while there are still outer brackets left
		S = S.substr(1, S.length() - 2); //remove first and last character
	}
	return S;//return stripped expression
}

bool validForm(string S){//checks if this expression contains valid characters and begins and ends with a number (- sign exception for beginning)
    S = strip(S);//removes exccess brackets
    int br = 0;//bracket stack counter
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
    if ((S[0] == '+') || (S[0] == '*') || (S[0] == '/')){//if fist character is an operator and not a '-'
        return false;//invalid expression
    }
    
    //Last Character Check:
    if ((S[S.length()-1] == '-') || (S[S.length()-1] == '+') || (S[S.length()-1] == '*') || (S[S.length()-1] == '/')){//last character is an operator of any kind
        return false;//invalid expression
    }
    return true;//all tests passed, valid expression
}

bool expCheck(string str){//now checks the expression for operator number coherency
    string S = strip(str);
    
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

   
   


void parse(string S, string &ls, char &op, string &rs) {
	form(S);
	int opIndex = 0; //Index of the first highest order OP
	int bLevel; //we're only interested in operators OUTSIDE of brackets
	//loop through characters
	for (int i = 0; i < S.length(); i++) {
		if (S[i] == '(')
			bLevel += 1; //Bracket level increased
		if (S[i] == ')')
			bLevel -= 1; //Bracket level decreased
		//look for OPs
		if ((bLevel == 0) && check(ops, S[i])) {//outside of brackets and found an operator
			if (BEDMAS(S[i]) > BEDMAS(S[opIndex])) { //if the new operator is of higher order
				opIndex = i;
			}
		}
	}
	//left side is everything left of the opindex
	ls = S.substr(0, opIndex + 1);
	//right side is everything right of the opIndex
	rs = S.substr(opIndex + 1, S.length() - (opIndex + 1));
	op = S[opIndex];
}

ArithmeticExpression* makeRoot(string &user_input) {
	string ls(""), rs("");
	char op('0');
	parse(user_input, ls, op, rs);      //parse initial expression
	if (op == '+') {
		Addition *root =new Addition(ls, rs, false);
		return root; //make a different expression object depending on the operator.
	}
	Addition *root =new Addition(ls, rs, false);
	return root;

}
void makeTree(ArithmeticExpression* RootExpression, bool left) { //recursive function to build the Expression tree.
	string ls(""), rs("");
	char op('0');
	if (RootExpression->leaf == true) {
		return;
	} else {
		if (left) parse(RootExpression->leftstring, ls, op, rs);

		else parse(RootExpression->rightstring, ls, op, rs);


		if (op == '+')
			Addition *Child = new Addition(ls, rs, false);


		if (left)
			RootExpression->left=Child; //pointer to the evaluate function of the child

		else
			RootExpression->right=Child;

		makeTree(Child, true);
		makeTree(Child, false);

	}
}

int main() {
	string user_input = "";
	while (user_input != "#") {
		cout << "Please enter an expression: " << endl;
		cin >> user_input;
		Expression* root = makeRoot(user_input);
		cout << (root->evaluate());

	}
	return 0;
}
