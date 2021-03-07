#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

int string_size;

typedef struct list
{
    char output;
    struct list * prev;
    struct list * next;
}List;

List * add_item(char , List *);
List * delete_item(List *, char *);
List * rewind_list(List * );
void print_list(List * );


#endif // LIST_H_INCLUDED
