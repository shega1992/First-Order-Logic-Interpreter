#include <stdio.h>
#include "parser.h"
#include "stack.h"
#include "list.h"

long current_position;

bool Parse_Program(void)
{
     if(Parse_Expression() && expect_token(TOKEN_LINEFEED))
        return true;
     else
     {
         printf("parse error: unexpected token %s\n", token_string(scan_token()));
         return false;
     }
}

bool Parse_Expression(void)
{
    return Parse_Value() && Parse_Expression_Prime();
}

bool Parse_Expression_Prime(void)
{
    token_t t = scan_token();
    if(t == TOKEN_AND || t == TOKEN_OR || t == TOKEN_IMPLICATION)
        return Parse_Value() && Parse_Expression_Prime();
    else
    {
        putback_token(t);
        return true;
    }
}

bool Parse_Value(void)
{
    if(Parse_NOT() && expect_token(TOKEN_LPARENTHESIS))
        return Parse_Expression() && expect_token(TOKEN_RPARENTHESIS) && Parse_Expression_Prime();
    token_t t = scan_token();
    if(t == TOKEN_TRUE || t == TOKEN_FALSE)
        return true;
    else
    {
        printf("parse error: unexpected token %s\n", token_string(t));
        return false;
    }
}

bool Parse_NOT(void)
{
    token_t t = scan_token();
    if(t == TOKEN_NOT)
        return true;
    else
    {
        putback_token(t);
        return true;
    }
}

token_t scan_token(void)
{
    int temp;
    current_position = ftell(fp);
    fscanf(fp,"%d", &temp);
    return temp;
}

bool expect_token(token_t t)
{
   if(t == scan_token())
        return true;
    else
    {
        putback_token(t);
        return false;
    }
}

void putback_token(token_t t)
{
    fseek(fp, current_position, SEEK_SET);
}

char * token_string(token_t t)
{
    switch(t)
    {
        case TOKEN_LINEFEED: return "LINEFEED";
        case TOKEN_TRUE: return "TRUE";
        case TOKEN_FALSE: return "FALSE";
        case TOKEN_AND: return "AND";
        case TOKEN_OR: return "OR";
        case TOKEN_NOT: return "NOT";
        case TOKEN_IMPLICATION: return "IMPLICATION";
        case TOKEN_LPARENTHESIS: return "LEFT PARENTHESIS";
        case TOKEN_RPARENTHESIS: return "RIGHT PARENTHESIS";
    }
}

void evaluate_expression(void)
{
    Stack * operators = NULL;
    List * output_string = NULL;
    token_t t;
    char ch;
    fseek(fp, 0, SEEK_SET);

    while((t = scan_token()))
    {
        switch(t)
        {
            case TOKEN_TRUE:
                output_string = add_item('T', output_string);
                break;
            case TOKEN_FALSE:
                output_string = add_item('F', output_string);
                break;
            case TOKEN_AND:
                 while(number_of_operators >= 1 && operators -> op_priority >= AND_PRIORITY && operators -> operator != '(')
                 {
                     operators = pop(operators, &ch);
                     output_string = add_item(ch, output_string);
                 }
                 operators = push('&', AND_PRIORITY, operators);
                 break;
            case TOKEN_OR:
                while(number_of_operators >= 1 && operators -> op_priority >= OR_PRIORITY && operators -> operator != '(')
                 {
                     operators = pop(operators, &ch);
                     output_string = add_item(ch, output_string);
                 }
                 operators = push('|', OR_PRIORITY, operators);
                 break;
            case TOKEN_NOT:
                 operators = push('!', NOT_PRIORITY, operators);
                 break;
            case TOKEN_IMPLICATION:
                while(number_of_operators >= 1 && operators -> op_priority >= IMPLICATION_PRIORITY && operators -> operator != '(')
                 {
                     operators = pop(operators, &ch);
                     output_string = add_item(ch, output_string);
                 }
                 operators = push('@', IMPLICATION_PRIORITY, operators);
                 break;
            case TOKEN_LPARENTHESIS:
                operators = push('(', PARENTHESIS_PRIORITY, operators);
                break;
            case TOKEN_RPARENTHESIS:
                while(operators -> operator != '(')
                {
                    operators = pop(operators, &ch);
                    output_string = add_item(ch, output_string);
                }
                operators = pop(operators, &ch); // pop '('
                break;
        }
    }

    while(operators != NULL)
    {
        operators = pop(operators, &ch);
        output_string = add_item(ch, output_string);
    }

    fputs("Reverse Polish notation: ",stdout);
    output_string = rewind_list(output_string);
    print_list(output_string);

    while(string_size > 1)
    {
        if(output_string -> output == '&')
        {
            output_string = delete_item(output_string, &ch); // delete operator
            output_string = delete_item(output_string, &ch); // delete value
            output_string -> output = truth_table(output_string -> output, ch, '&');

        }
        else if(output_string -> output == '|')
        {
            output_string = delete_item(output_string, &ch);
            output_string = delete_item(output_string, &ch);
            output_string -> output = truth_table(output_string -> output, ch, '|');
        }
        else if(output_string -> output == '!')
        {
            output_string = delete_item(output_string, &ch);
            output_string -> output = truth_table(' ', output_string -> output, '!');
        }
        else if(output_string -> output == '@')
        {
            output_string = delete_item(output_string, &ch);
            output_string = delete_item(output_string, &ch);
            output_string -> output = truth_table(output_string -> output, ch, '@');
        }
        else
            output_string = output_string -> next;
    }

    (output_string -> output == 'T')? puts("Result: true") : puts("Result: false");
    delete_item(output_string, &ch);
}



char truth_table(char val_1, char val_2, char op)
{
    switch(op)
    {
        case '&':
            if(val_1 == 'F' || val_2 == 'F')
                return 'F';
            else
                return 'T';
        case '|':
            if(val_1 == 'T' || val_2 == 'T')
                return 'T';
            else
                return 'F';
        case '!':
            if(val_2 == 'T')
                return 'F';
            else
                return 'T';
        case '@':
            if(val_1 == 'T' && val_2 == 'T')
                return 'T';
            else if(val_1 == 'T' && val_2 == 'F')
                return 'F';
            else if(val_1 == 'F' && val_2 == 'T')
                return 'T';
            else
                return 'T';
    }
}
