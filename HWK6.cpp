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
		if (c == ops[i])
			return i / 2;
	}
	return -1; // not an operator
}

bool check(const char a[], char c) {
	int i = 0;// index variable
	while (!(a[i]=='\0')){
	    if (a[i] == c){
	        return true;
	    }
	    i++;
	}
	return false;
}

int brackClose(string S) {
	int stack = 0;
	for (int i = 0; i < S.length(); i++) {
		if (S[i] == '(')
			stack += 1; //Bracket level increased
		if (S[i] == ')') {
			stack -= 1; //Bracket level decreased
			if (stack == 0)
				return i; //returns the index at which the entire bracket stack was cleared
		}
	}
	return -1; //something bad happened
}

//This function strips away the outer brackets of an expression, i.e. ((((((3+4)))))) becomes 3+4
string strip(string S) {
	while ((S[0] == '(') && (brackClose(S) == S.length() - 1)) {
		S = S.substr(1, S.length() - 2); //inclusive
	}
	return S;
}

bool validForm(string S){
    S = strip(S);
    int br = 0;
    for (int i = 0; i < S.length(); i++){
        if((!check(ops,S[i])) && (!check(digit,S[i])) && (!check(brackets,S[i])) && (!(S[i]==' '))){
            return false;
        }
            
        
        if (S[i] == '('){
            br++;
        }else if (S[i] == ')'){
            br--;
        }
        if (br < 0){
        	return false;
        }
    }
    if (!(br == 0 )){
        return false;
    }
    //First Character checks:
    if ((S[0] == '+') || (S[0] == '*') || (S[0] == '/')){
        return false;
    }
    
    //Last Character Check:
    if ((S[S.length()-1] == '-') || (S[S.length()-1] == '+') || (S[S.length()-1] == '*') || (S[S.length()-1] == '/')){
        return false;
    }
    return true;
}

bool expCheck(string str){
    string S = strip(str);
    
    bool O = false;
    bool N = false;
    bool Sp = false;
    bool carry = true;
    for (int i = 0; i < S.length(); i++){
        
        if (check(ops,S[i])){
        
            if (O){
                return false;
            }
            N = false;
            O = true;
            Sp = false;
        }
        else if(check(digit,S[i])){

            if (N && Sp){
                return false;
            }
            if (O){
                O = false;
            }
            N = true;
            Sp = false;
        }
        else if(check(brackets,S[i])){

            if (N){
                
                return false;
            }
            if (O){
                O = false;
            }
            N = true;
            Sp = false;

            string sub = S.substr(i);

            int end = brackClose(sub);
            sub = S.substr(i, end+1);

            carry = validForm(sub) && expCheck(sub);
            if (!carry){
                return false;
            }
            i = end+i;
        }else{
            Sp = true;
        }
        cout << O << " "<< N << " "<< Sp << endl;
    }
    return true;
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
