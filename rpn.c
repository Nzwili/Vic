#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Stack structure
typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

// Function prototypes
void push(Stack *stack, char c);
char pop(Stack *stack);
char peek(Stack *stack);
int isEmpty(Stack *stack);
int precedence(char c);
void infixToPrefix(char *infix, char *prefix);
void reverseString(char *str);

int main() {
    char infix[MAX_SIZE];
    char prefix[MAX_SIZE];

    printf("Enter the infix expression: ");
    fgets(infix, MAX_SIZE, stdin);
    infix[strlen(infix) - 1] = '\0'; // Removing the newline character

    infixToPrefix(infix, prefix);
    printf("Prefix expression: %s\n", prefix);

    return 0;
}

// Function to push an element onto the stack
void push(Stack *stack, char c) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->data[++stack->top] = c;
}

// Function to pop an element from the stack
char pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

// Function to return the top element of the stack
char peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}

// Function to check if the stack is empty
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Function to determine the precedence of an operator
int precedence(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return 0;
    }
}

// Function to convert infix expression to prefix expression
void infixToPrefix(char *infix, char *prefix) {
    Stack stack;
    stack.top = -1;

    reverseString(infix); // Reverse the infix expression

    int i = 0, j = 0;
    while (infix[i] != '\0') {
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                prefix[j++] = infix[i++];
            }
            prefix[j++] = ' ';
        } else if (infix[i] == ')') {
            push(&stack, infix[i++]);
        } else if (infix[i] == '(') {
            while (!isEmpty(&stack) && peek(&stack) != ')') {
                prefix[j++] = pop(&stack);
            }
            pop(&stack); // Pop '('
            i++;
        } else {
            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(infix[i])) {
                prefix[j++] = pop(&stack);
            }
            push(&stack, infix[i++]);
        }
    }

    // Pop remaining operators from stack
    while (!isEmpty(&stack)) {
        prefix[j++] = pop(&stack);
    }
    prefix[j] = '\0';

    // Reverse the result to get prefix expression
    reverseString(prefix);
}

// Function to reverse a string
void reverseString(char *str) {
    int len = strlen(str);
    int i, j;
    char temp;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}
