#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s -key\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(!strcmp(argv[1],"-scan"))
        yylex(fp,argv[1]);
    else if(!strcmp(argv[1],"-parse"))
    {
        if ((fp = fopen("tokens.txt", "w+")) == NULL)
        {
            fprintf(stderr,"Can't create tokens.txt\n");
            exit(EXIT_FAILURE);
        }

        yylex(fp,argv[1]);
        rewind(fp);
        (Parse_Program())? printf("Success. No errors in expression\n") : fprintf(stderr,"Failure\a\n");

         fclose(fp);
         if(remove("tokens.txt") != 0)
             fprintf(stderr,"Can't delete tokens.txt\a\n");
    }
    else if(!strcmp(argv[1],"-get"))
    {
        if ((fp = fopen("tokens.txt", "w+")) == NULL)
        {
            fprintf(stderr,"Can't create tokens.txt\n");
            exit(EXIT_FAILURE);
        }

        yylex(fp,argv[1]);
        rewind(fp);
        if(Parse_Program())
        {
            printf("Success. No errors in expression\n");
            evaluate_expression();
        }
        else
            fprintf(stderr,"Failure\a\n");

         fclose(fp);
         if(remove("tokens.txt") != 0)
             fprintf(stderr,"Can't delete tokens.txt\a\n");
    }
    else
    {
         fprintf(stderr,"Error. Unknown key\a\n");
         exit(EXIT_FAILURE);
    }

    return 0;
}
