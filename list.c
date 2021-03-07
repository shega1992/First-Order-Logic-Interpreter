#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List * add_item(char ch, List * tail)
{
    List *item = (List *)malloc(sizeof(List));
    if(item == NULL)
    {
        puts("Memory allocation failed. List is full.Program terminated");
        exit(EXIT_FAILURE);
    }
    item -> output = ch;
    item -> prev = tail;
    item -> next = NULL;
    if(tail != NULL)
        tail ->next = item;
    tail = item;
    string_size++;

    return tail;
}

List * delete_item(List * item, char * ch)
{
    List * temp = item;
    *ch = temp -> output;
    if(temp -> prev != NULL)
        temp -> prev -> next = temp -> next;
    if(temp -> next != NULL)
        temp -> next -> prev = temp -> prev;
    item = temp -> prev;
    string_size--;
    free(temp);

    return item;
}

List * rewind_list(List * output_string)
{
    while(output_string -> prev != NULL)
        output_string = output_string -> prev;
    return output_string;
}

void print_list(List * output_string)
{
    while(output_string != NULL)
    {
        printf("%c ", output_string -> output);
        output_string = output_string -> next;
    }
    puts("");
}
