#include "stackHead.h"
#include "stackImp.cpp"
#include "Tree.h"
#include "Tree.cpp"
#include <iostream>
#include<math.h>
#include <sstream>
#include <string>


using namespace std;


enum symbolType { OPERATOR, OPERAND, UNKNOWN };
enum preced { PCPAR = 1, PADD = 5, PMULT = 10, PEXP = 20, PSIGN = 5, POPAR = 0, PDIV=10 };
enum Operators {CPAR = ')', ADD = '+', SUB = '-', MULT = '*', DIV = '/', EXP = '^', OPAR = '(' };
int symbolType(char symbol);
int precValue(char symbol) ;
int associativity(char opr) ;
int toPostfix(string infix, string & postfix) ;
double evaluate(nodeTree<tokens> *root);


int main(){
	char choice='Y';
	do{
	system("cls");
	string infix;
	string postfix="";
	bool error=false;
	cout << "Enter the binary expression: ";
    cin>>infix;
	int c=toPostfix(infix,postfix);
	if(c==-1){
		cout<<"Please check your expression\n";
	}
	else{
		cout<<"Postfix notation: "<<postfix<<"\n";
		tokens ts;
    	char skip;
    	Stack < nodeTree <tokens> * > s1;
    	stringstream ss(postfix);
    	ss.seekg(0, ios::beg);
    	while(!ss.eof() && error==false) {
    		if(ss.peek()!=','){
				if(symbolType(ss.peek()) == OPERATOR){
					ss>>ts.value.operators;
					ts.type=1;
					nodeTree <tokens> *tsn=new nodeTree<tokens>();
					tsn->data=ts;
					if(s1.isEmpty()) error=true;
					else tsn->right=s1.pop();
					if(s1.isEmpty()) error=true;
					else tsn->left=s1.pop();
					s1.push(tsn);
				}
			else if (symbolType(ss.peek()) == OPERAND){
					ss>>ts.value.operand;
					ts.type=2;
					nodeTree <tokens> *tsn=new nodeTree<tokens>();
					tsn->data=ts;
					tsn->left=tsn->right=NULL;
					s1.push(tsn);
				}
			}
			else	ss>>skip;
		}
		if(error==true){
			cout<<"Please check operation\n";
		}
		else{
			nodeTree <tokens> *temp;
			temp=s1.peep();
			cout<<evaluate(temp)<<"\n";
		}
	}
	cout<<"Enter y or Y to repeat\n";
	cin>>choice;
	}while(choice=='Y' || choice=='y');
	cout<<"GOODBYE";							
	return 0;
}

int symbolType(char symbol){
	if (symbol == CPAR || symbol == ADD || symbol==SUB||symbol==MULT||symbol==DIV||symbol==EXP||symbol==OPAR) {
		return OPERATOR;

	}
	else if ((symbol >= 'a' && symbol <= 'z') || (symbol >= '0' && symbol <= '9') || (symbol >= 'A' && symbol <= 'Z')) {
		return OPERAND;
	}
	else {
		return UNKNOWN;
	}
}

int precValue(char symbol) {
	if (symbol == CPAR)
		return PCPAR;
	else if (symbol == ADD)
		return PADD;
	else if (symbol == SUB)
		return PSIGN;
	else if (symbol == MULT)
		return PMULT;
	else if (symbol == EXP)
		return PEXP;
	else if (symbol == OPAR)
		return POPAR;
	else if (symbol == DIV)
		return PDIV;

return -1;
}

int associativity(char opr) {
	if (opr == EXP) return 1;
	else return 0;
}

int toPostfix(string infix, string & postfix){
	int len=infix.length();
	double num;
    char opr,opr2;
    int precV,precV2,ac;
    Stack <char> s1;
    stringstream nu;
    stringstream ss(infix);
    ss.seekg(0, ios::beg);
    while(!ss.eof() && len!=0) {
    	if (symbolType(ss.peek()) == OPERATOR) {
                ss>>opr;
                if(s1.isEmpty()){
                	s1.push(opr);
				}
				else{
				 precV=precValue(opr);
				 precV2=precValue(s1.peep());
				 if(precV==0){
				 	s1.push(opr);
				 }
				 else if(precV2==0){
				 	s1.push(opr);
				 }
				 else if(precV==1){
				 	while(precV2!=0){
				 		opr2=s1.pop();
				 		nu<<opr2;
				 		nu<<',';
				 		if(s1.isEmpty()) break;
				 		precV2=precValue(s1.peep());
					 }
					 s1.pop();
				 }
				 else if(precV>precV2){
				 	s1.push(opr);
				 }
				 else{
				 	while(precV<=precV2){
				 		ac=associativity(opr);
				 		if(ac==1) break;
				 		else{
				 			opr2=s1.pop();
				 			nu<<opr2;
				 			nu<<','; 
						}
						if(s1.isEmpty()) break;
						precV2=precValue(s1.peep());
					}
					s1.push(opr);
				 }
				}
        }
        else if (symbolType(ss.peek()) == OPERAND){
            ss>>num;
            nu<<num;
            nu<<',';    
		}
		else if(symbolType(ss.peek()) == UNKNOWN){
			ss>>opr;
			return -1;
		}
		len--;
	}
	while(!s1.isEmpty()){
		nu<<s1.pop();
		if(!s1.isEmpty()) nu<<',';
	}
	nu>>postfix;
	return 1;
}

double evaluate(nodeTree<tokens> *root){
	if(!root)
		return 0;
	if(!root->left && !root->right)
		return root->data.value.operand;
		
	double left_val=evaluate(root->left);
	double right_val=evaluate(root->right);
	
	if(root->data.value.operators=='+')
		return left_val + right_val;
	if(root->data.value.operators=='-')
		return left_val - right_val;
	if(root->data.value.operators=='*')
		return left_val * right_val;
	if(root->data.value.operators=='/')
		return left_val / right_val;
	if(root->data.value.operators=='^')
		return pow(left_val,right_val);
}




