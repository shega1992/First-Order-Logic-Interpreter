#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <stdbool.h>

typedef enum
{
   TOKEN_LINEFEED,
   TOKEN_TRUE,
   TOKEN_FALSE,
   TOKEN_AND,
   TOKEN_OR,
   TOKEN_NOT,
   TOKEN_IMPLICATION,
   TOKEN_LPARENTHESIS,
   TOKEN_RPARENTHESIS
}token_t;

FILE *fp;

void yylex(FILE *, char *);

bool Parse_Program(void);
bool Parse_Expression(void);
bool Parse_Expression_Prime(void);
bool Parse_Value(void);
bool Parse_NOT(void);
token_t scan_token(void);
bool expect_token(token_t );
void putback_token(token_t );
char * token_string(token_t );
void evaluate_expression(void);
char truth_table(char , char , char );

#endif // PARSER_H_INCLUDED
