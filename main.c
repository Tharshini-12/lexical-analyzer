/* Name        : Tharshini S
   Date        : 12-05-2026
   File Name   : main.c
   Title       : Lexical Analyzer  */

#include "lexical_analyzer.h"

int main(int argc, char *argv[])
{
    //check command line count
    if(argc<2)
    {
        printf("Usage: ./a.out <samplefile.c\n");
        return 1;
    }

    initializeLexer(argv[1]); //open source file

        Token token; //structure variable to store token

        //read tokens until EOF
        while((token=getNextToken()).type != UNKNOWN)
        {
            switch(token.type) //print token based on token type
            {
                //keyword token
                case KEYWORD:
                printf("Keyword           : %s\n",token.tok_str);
                break;

                //identifier token
                case IDENTIFIER:
                printf("Identifier        : %s\n",token.tok_str);
                break;

                //operator token
                case OPERATOR:
                printf("Operator          : %s\n",token.tok_str);
                break;

                //special character token
                case SPECIAL_CHARACTER:
                printf("Special character : %s\n",token.tok_str);
                break;

                //constant/literal token
                case CONSTANT:
                printf("Literal           : %s\n",token.tok_str);
                break;

                default:
                break;
            }
        }
        return 0;

}

