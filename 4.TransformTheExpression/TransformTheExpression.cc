#include <string>
#include <iostream>
#include <stack>
#include <map>

using namespace std;

enum Associativity {
	kLeftAssoc = 1,
	kRightAssoc = 2,
};

class InfixToPostfix {
public:
	InfixToPostfix();
	string convert(string infix_expr);
private:
	map<char, int> m_precedence;
	map<char, Associativity> m_assoc;
};

InfixToPostfix::InfixToPostfix() {
	m_precedence['+'] = 1;
	m_assoc['+'] = kLeftAssoc;
	m_precedence['-'] = 1;
	m_assoc['-'] = kLeftAssoc;
	m_precedence['*'] = 2;
	m_assoc['*'] = kLeftAssoc;
	m_precedence['/'] = 2;
	m_assoc['/'] = kLeftAssoc;
	m_precedence['^'] = 3;
	m_assoc['^'] = kRightAssoc;
}

string InfixToPostfix::convert(string infix_expr) {
	stack<char> op_stack;
	string postfix_expr;
	for (string::iterator iter = infix_expr.begin(); 
		iter != infix_expr.end(); ++iter) {
		if (m_precedence.find(*iter) != m_precedence.end()) {
			// this is an operator
			int op_precedence = m_precedence[*iter];
			while (!op_stack.empty() && op_stack.top() != '(' &&
				((m_assoc[*iter] == kLeftAssoc && op_precedence == m_precedence[op_stack.top()]) ||
				op_precedence < m_precedence[op_stack.top()])) {
				postfix_expr += op_stack.top();
				op_stack.pop();
			}
			op_stack.push(*iter);
		} else if (*iter == '(') {
			op_stack.push(*iter);
		} else if (*iter == ')') {
			while (!op_stack.empty() && op_stack.top() != '(') {
				postfix_expr += op_stack.top();
				op_stack.pop();
			}
			// pop '('
			op_stack.pop();
		} else { // this is an operand
			postfix_expr += *iter;
		}
	}
	while (!op_stack.empty()) {
		postfix_expr += op_stack.top();
		op_stack.pop();
	}
	return postfix_expr;
}

int main() {
	InfixToPostfix converter;
	int num_cases;
	cin >> num_cases;
	string infix_expr;
	while (num_cases-- > 0) {
		cin >> infix_expr;
		cout << converter.convert(infix_expr) << endl;
	}
	return 0;
}




