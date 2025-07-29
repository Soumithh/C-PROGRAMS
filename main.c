#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char stack[100];           
char postfix[200];         // Increase size for spaces and multi-digit
char infix[100];           
int evaluate[100];         
int top = -1;              
int evaltop = -1;          
int postfixcounter = 0;    

void push(char c) {
    stack[++top] = c;
}

char pop() {
    if (top == -1)
        return -1;
    return stack[top--];
}

int priority(char c) {
    if (c == '(') return 0;
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return -1;
}

int isrightassociative(char c) {
    return (c == '^');  
}

void intpush(int a) {
    evaluate[++evaltop] = a;
}

int intpop() {
    if (evaltop == -1)
        return -999;
    return evaluate[evaltop--];
}

void infixtopostfix() {
    int i = 0;
    while (infix[i] != '\0') {
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                postfix[postfixcounter++] = infix[i++];
            }
            postfix[postfixcounter++] = ' '; // space after number
            i--; // go back one since outer loop also increments
        }
        else if (infix[i] == '(') {
            push(infix[i]);
        }
        else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[postfixcounter++] = pop();
                postfix[postfixcounter++] = ' ';
            }
            pop(); // remove '('
        }
        else {
            while (top != -1 && stack[top] != '(' &&
                   (priority(stack[top]) > priority(infix[i]) ||
                    (priority(stack[top]) == priority(infix[i]) && !isrightassociative(infix[i])))) {
                postfix[postfixcounter++] = pop();
                postfix[postfixcounter++] = ' ';
            }
            push(infix[i]);
        }
        i++;
    }

    while (top != -1) {
        postfix[postfixcounter++] = pop();
        postfix[postfixcounter++] = ' ';
    }

    postfix[postfixcounter] = '\0'; 
}

void evaluatepostfix() {
    int i = 0;
    char token[20];
    while (postfix[i] != '\0') {
        if (isdigit(postfix[i])) {
            int j = 0;
            while (isdigit(postfix[i])) {
                token[j++] = postfix[i++];
            }
            token[j] = '\0';
            intpush(atoi(token));
        }
        else if (postfix[i] != ' ') {
            int b = intpop();
            int a = intpop();
            switch (postfix[i]) {
                case '+': intpush(a + b); break;
                case '-': intpush(a - b); break;
                case '*': intpush(a * b); break;
                case '/': 
                    if (b == 0) {
                        printf("error division by zero");
                        exit(1);
                    }
                    intpush(a / b); break;
                case '^': intpush(pow(a, b)); break;
                default: intpush(-999);
            }
        }
        i++;
    }
}

int main() {
    printf("Enter the infix expression:\n");
    scanf("%s", infix);

    if (strlen(infix) > 100) {
        printf("Failed overflow\n");
        return 1;
    }

    printf("Postfix expression: ");
    infixtopostfix();
    printf("%s\n", postfix);
    evaluatepostfix();
    printf("RESULTANT VALUE OF THE EXPRESSION = %d\n", evaluate[0]);

    return 0;
}
