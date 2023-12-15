
#include<iostream>
#include<stack>
#include<string>

using namespace std;

// function to convert infix expression to postfix 
string infixtopostfix(string expression);

// function to verify whether an operator has higher precedence over other
int hashigherprecedence(char operator1, char operator2);

// function to verify whether a character is operator symbol or not. 
bool isoperator(char c);

// function to verify whether a character is alphanumeric chanaracter (letter or numeric digit) or not. 
bool isoperand(char c);

void main() 
{
	string expression; 
	cout<<"enter infix expression \n";
	getline(cin,expression);
	string postfix = infixtopostfix(expression);
	cout<<"output = "<<postfix<<"\n";
system("pause");
}

// function to evaluate postfix expression and return output
string infixtopostfix(string expression)
{
	// declaring a stack from standard template library in c++. 
	stack<char> s;
	string postfix = ""; // initialize postfix as empty string.
	for(int i = 0;i< expression.length();i++) {

		// scanning each character from left. 
		// if character is a delimitter, move on. 
		if(expression[i] == ' ' || expression[i] == ',') continue; 

		// if character is operator, pop two elements from stack, perform operation and push the result back. 
		else if(isoperator(expression[i])) 
		{
			while(!s.empty() && s.top() != '(' && hashigherprecedence(s.top(),expression[i]))
			{
				postfix+= s.top();
				s.pop();
			}
			s.push(expression[i]);
		}
		// else if character is an operand
		else if(isoperand(expression[i]))
		{
			postfix +=expression[i];
		}

		else if (expression[i] == '(') 
		{
			s.push(expression[i]);
		}

		else if(expression[i] == ')') 
		{
			while(!s.empty() && s.top() !=  '(') {
				postfix += s.top();
				s.pop();
			}
			s.pop();
		}
	}

	while(!s.empty()) {
		postfix += s.top();
		s.pop();
	}

	return postfix;
}

// function to verify whether a character is english letter or numeric digit. 
// we are assuming in this solution that operand will be a single character
bool isoperand(char c) 
{
	if(c >= '0' && c <= '9') return true;
	if(c >= 'a' && c <= 'z') return true;
	if(c >= 'a' && c <= 'z') return true;
	return false;
}

// function to verify whether a character is operator symbol or not. 
bool isoperator(char c)
{
	if(c == '+' || c == '-' || c == '*' || c == '/' || c== '$')
		return true;

	return false;
}

// function to verify whether an operator is right associative or not. 
int isrightassociative(char op)
{
	if(op == '$') return true;
	return false;
}

// function to get weight of an operator. an operator with higher weight will have higher precedence. 
int getoperatorweight(char op)
{
	int weight = -1; 
	switch(op)
	{
	case '+':
	case '-':
		weight = 1;
	case '*':
	case '/':
		weight = 2;
	case '$':
		weight = 3;
	}
	return weight;
}

// function to perform an operation and return output. 
int hashigherprecedence(char op1, char op2)
{
	int op1weight = getoperatorweight(op1);
	int op2weight = getoperatorweight(op2);

	// if operators have equal precedence, return true if they are left associative. 
	// return false, if right associative. 
	// if operator is left-associative, left one should be given priority. 
	if(op1weight == op2weight)
	{
		if(isrightassociative(op1)) return false;
		else return true;
	}
	return op1weight > op2weight ?  true: false;
	
}