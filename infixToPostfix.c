#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int precedence(char operator) {
	switch(operator) {
		case '$':
			return 0;
		case '(':
			return 1;	
		case '+':
		case '-':
			return 2;
		case '*':
		case '/':
			return 3;
		case '^':
			return 4;			 
	}
}

void push (char *stack, int top, int MAX, char val) {
	if (top < MAX-1) {
		stack[top] = val;
	} else {
		printf("Stack is full!");
	}
}

char pop (char *stack, int top, int MAX) {
	if (top > -1) 
		return stack[top]; 
	return '\0';	
}

void infixToPostfix(char *infix, char *postfix) {
	int i, k = 0, top = -1;
	char stack[100], topElement;
	top++;
	push(stack, top, 100, '$');
	for (i=0; infix[i]!='\0'; i++) {
		if (infix[i] >= '0' && infix[i] <= '9') {
			postfix[k++] = infix[i];
		} else if (infix[i] == '(') {
			top++;
			push(stack, top, 100, infix[i]);
	    } else if (infix[i] == ')') {
	    	while (stack[top] != '(') {
	    		postfix[k++] = pop(stack, top, 100);
	    		top--;
			}
			pop(stack, top, 100);
			top--;
		} else {
			while (precedence(infix[i]) <= precedence(stack[top])) {
				postfix[k++] = pop(stack, top, 100);
				top--;
			}
			top++;	
			push(stack, top, 100, infix[i]);	
		}
	}
	while (stack[top] != '$') {
		postfix[k++] = pop(stack, top, 100);
		top--;
    }
	postfix[k] = '\0';	
}

int solvePostfix(char *postfix) {
	int i, top = -1, operand1, operand2, ans, solvingStack[100];
	for (i=0; postfix[i] != '\0'; i++) {
		if (postfix[i] >='0' && postfix[i] <='9') {
			top++;
			push (solvingStack, top, 100, postfix[i]-'0');
		} else {
				operand2 = pop(solvingStack, top, 100);
				top--;
				operand1 = pop(solvingStack, top, 100);
				top--;
			switch (postfix[i]) {
				case '+':
					ans = operand1 + operand2;
					break;
				case '-':
					ans = operand1 - operand2;
					break;
				case '*':
					ans = operand1 * operand2;
					break;
				case '/':
					ans = operand1 / operand2;
					break;
				case '^':
					ans = pow(operand1, operand2);				
					break;
			}			
			top++;
			push (solvingStack, top, 100, ans);
		}
	}
	printf("%d", top);
	ans = pop(solvingStack, top, 100);
	top--;
	return ans;
}

int main() {
	char infixExpression[100];
	printf("Enter a infix expression: ");
	scanf("%s", infixExpression);
	char *postfixExpression;
	postfixExpression = (char *)malloc(100);
	infixToPostfix(infixExpression, postfixExpression);
	printf("The postfix of the entered expression is ");
	puts(postfixExpression);
	printf("The solution of expression is %d", solvePostfix(postfixExpression));
	return 0;
}
