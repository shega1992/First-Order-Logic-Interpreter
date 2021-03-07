#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack * push(char op, int priority, Stack * top)
{
    Stack * item = (Stack *)malloc( sizeof(Stack));
    if(item == NULL)
    {
        puts("Memory allocation failed. Stack is full.Program terminated");
        exit(EXIT_FAILURE);
    }
    item -> operator = op;
    item -> op_priority = priority;
    item -> next = top;
    top = item;
    number_of_operators++;

    return top;
}

Stack * pop(Stack * top, char *op)
{
    Stack *temp = top;
    *op = temp -> operator;
    top = top -> next;
    number_of_operators--;
    free(temp);

    return top;
}
