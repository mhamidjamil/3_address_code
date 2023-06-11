// I prefer C++ on C as it have better support for strings.
// SP19-BCS-098
// M Hamid Jamil
#include <iostream>
#include <stack>
#include <string>
int temp_index = 1;
using namespace std;

bool isOperator(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/');
}

int getPrecedence(char c) {
  if (c == '+' || c == '-') {
    return 1;
  } else if (c == '*' || c == '/') {
    return 2;
  }
  return 0;
}

string convertToThreeAddressCode(const string &expression) {
  stack<char> operators;
  stack<string> operands;
  string threeAddressCode;

  for (char c : expression) {
    if (isOperator(c)) {
      while (!operators.empty() && operators.top() != '(' &&
             getPrecedence(operators.top()) >= getPrecedence(c)) {
        char op = operators.top();
        operators.pop();

        string operand2 = operands.top();
        operands.pop();

        string operand1 = operands.top();
        operands.pop();

        string temp = "t" + to_string(temp_index++);
        threeAddressCode +=
            temp + " = " + operand1 + " " + op + " " + operand2 + "\n";

        operands.push(temp);
      }

      operators.push(c);
    } else if (c == '(') {
      operators.push(c);
    } else if (c == ')') {
      while (!operators.empty() && operators.top() != '(') {
        char op = operators.top();
        operators.pop();

        string operand2 = operands.top();
        operands.pop();

        string operand1 = operands.top();
        operands.pop();

        string temp = "t" + to_string(temp_index++);
        threeAddressCode +=
            temp + " = " + operand1 + " " + op + " " + operand2 + "\n";

        operands.push(temp);
      }

      if (!operators.empty() && operators.top() == '(') {
        operators.pop();
      }
    } else {
      string operand(1, c);
      operands.push(operand);
    }
  }

  while (!operators.empty()) {
    char op = operators.top();
    operators.pop();

    string operand2 = operands.top();
    operands.pop();

    string operand1 = operands.top();
    operands.pop();

    string temp = "t" + to_string(temp_index++);
    threeAddressCode +=
        temp + " = " + operand1 + " " + op + " " + operand2 + "\n";

    operands.push(temp);
  }

  return threeAddressCode;
}

int main() {
  string infixExpression;
  cout << "Enter an arithmetic expression in infix notation: ";
  getline(cin, infixExpression);

  string threeAddressCode = convertToThreeAddressCode(infixExpression);
  cout << "Three Address Code:\n" << threeAddressCode;

  return 0;
}
