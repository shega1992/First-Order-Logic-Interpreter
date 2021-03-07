#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

int number_of_operators;

typedef struct stack
{
    char operator;
    int op_priority;
    struct stack * next;
}Stack;

enum {IMPLICATION_PRIORITY = 1, OR_PRIORITY, AND_PRIORITY, NOT_PRIORITY, PARENTHESIS_PRIORITY};

Stack * push(char , int , Stack *);
Stack * pop(Stack *, char *);

#endif // STACK_H_INCLUDED
