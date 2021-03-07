#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "parser.h"
#define SIZE 100


void yylex(FILE *fp, char * key)
{
    int counter = 0;
    char buffer[SIZE];
    fputs("Enter logic expression: ", stdout);
    fgets(buffer,SIZE, stdin);

    for(int i = 0; buffer[i] != '\n'; i++)
    {
       if(isspace(buffer[i]))
            continue;
       else if(buffer[i] == 'T')
           (!strcmp(key,"-scan"))? printf("%d.TRUE\n",++counter) : fprintf(fp,"%d ", TOKEN_TRUE);
       else if(buffer[i] == 'F')
           (!strcmp(key,"-scan"))? printf("%d.FALSE\n",++counter) : fprintf(fp,"%d ", TOKEN_FALSE);
       else if(buffer[i] == '&')
           (!strcmp(key,"-scan"))? printf("%d.AND\n",++counter) : fprintf(fp,"%d ", TOKEN_AND);
       else if(buffer[i] == '|')
           (!strcmp(key,"-scan"))? printf("%d.OR\n",++counter) : fprintf(fp,"%d ", TOKEN_OR);
       else if(buffer[i] == '!')
           (!strcmp(key,"-scan"))? printf("%d.NOT\n",++counter) : fprintf(fp,"%d ", TOKEN_NOT);
       else if(buffer[i] == '-')
       {
           if(buffer[++i] == '>')
               (!strcmp(key,"-scan"))? printf("%d.IMPLICATION\n",++counter) : fprintf(fp,"%d ", TOKEN_IMPLICATION);
           else
           {
               if(!strcmp(key,"-scan"))
                   printf("%d.ERROR\a\n",++counter);
               else
               {
                    fprintf(stderr,"Scan error\a\n");
                    fclose(fp);
                    if(remove("tokens.txt") != 0)
                        fprintf(stderr,"Can't delete tokens.txt\a\n");
                    exit(EXIT_FAILURE);
               }
           }
       }
       else if(buffer[i] == '(')
           (!strcmp(key,"-scan"))? printf("%d.LEFT PARENTHESIS\n",++counter) : fprintf(fp,"%d ", TOKEN_LPARENTHESIS);
       else if(buffer[i] == ')')
           (!strcmp(key,"-scan"))? printf("%d.RIGHT PARENTHESIS\n",++counter) : fprintf(fp,"%d ", TOKEN_RPARENTHESIS);
       else
       {
           if(!strcmp(key,"-scan"))
                printf("%d.ERROR\a\n",++counter);
            else
            {
                fprintf(stderr,"Scan error\a\n");
                fclose(fp);
                if(remove("tokens.txt") != 0)
                    fprintf(stderr,"Can't delete tokens.txt\a\n");
                exit(EXIT_FAILURE);
            }
       }
    }

    (!strcmp(key,"-scan"))? printf("%d.LINEFEED\n",++counter) : fprintf(fp,"%d ", TOKEN_LINEFEED);
}



