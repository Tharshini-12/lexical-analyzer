/* Name        : Tharshini S
   Date        : 12-05-2026
   File Name   : lexical_analyzer.c
   Title       : Lexical Analyzer source file */
   
#include "lexical_analyzer.h"

//keywords list
const char* keywords[MAX_KEYWORDS] = { "int", "float", "return", "if", "else", "while", "for", "do",
                                              "break", "continue","char", "double", "void", "switch", "case",
                                              "default", "const", "static", "sizeof", "struct" };
//supported operators and special characters list
const char* operators = "+-*/%=!<>|&";
const char* specialCharacters = ",;{}()[]";

FILE *fp; //file pointer to real the source file

//function to open source file
void initializeLexer(const char* filename)
{
    fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf("Error: Cannot open file %s\n",filename);
    }
}

//function to extract next token from source file
Token getNextToken()
{
    Token tok;
    //initialize token
    tok.tok_str[0]='\0';
    tok.type=UNKNOWN; //UNKNOWN is returned at end of file

    char ch;
    int i=0;

    //read character until end of the file
    while((ch=fgetc(fp))!=EOF)
    {
        //ignore preprocessor directive, #include <stdio.h>
        if(ch=='#')
        {
            while((ch=fgetc(fp))!=EOF && ch!='\n');
            continue;
        }

        //ignore spaces
        if(ch==' ')
        {
            continue;
        }

        //if keyword or identifier
        if(is_alpha(ch) || ch=='_')
        {
            tok.tok_str[i++]=ch;

            //read complete word
            while((ch=fgetc(fp))!=EOF && (is_alnum(ch) || ch=='_'))
            {
                tok.tok_str[i++]=ch;
            }
            tok.tok_str[i]='\0';

            //move 1 step back coz extra spaces already read
            if(ch!=EOF)
            {
                fseek(fp,-1,SEEK_CUR);
            }

            categorizeToken(&tok);//identify token type

            return tok;
        }

        //special character
        else if(strchr(specialCharacters,ch))
        {
            tok.tok_str[0]=ch;
            tok.tok_str[1]='\0';

            tok.type=SPECIAL_CHARACTER;
            return tok;
        }

        //constant-if digits
        else if(is_digit(ch))
        {
            tok.tok_str[i++]=ch;

            while((ch=fgetc(fp))!=EOF && (is_digit(ch)||ch=='.')) //read complete number
            {
                tok.tok_str[i++]=ch;
            }
            tok.tok_str[i]='\0';

            if(ch!=EOF) //move fp back
            {
                fseek(fp,-1,SEEK_CUR); //moving 1 char back from current position
            }

            categorizeToken(&tok);//identify token type
            return tok;
        }

        //if string literals
        else if(ch=='"')
        {
            tok.tok_str[i++]=ch;
            while((ch=fgetc(fp))!=EOF && ch!='"') //read until double quotation
            {
                tok.tok_str[i++]=ch;
            }
            tok.tok_str[i++]='"';
            tok.tok_str[i]='\0';

            tok.type=CONSTANT;
            return tok;
        }

        
        //if character literal
        else if(ch=='\'')
        {
            tok.tok_str[i++]=ch;
            while((ch=fgetc(fp))!=EOF && ch!='\'') //read until closing single quote
            {
                tok.tok_str[i++]=ch;
            }
            tok.tok_str[i++]='\'';
            tok.tok_str[i]='\0';

            tok.type=CONSTANT;
            return tok;
        }

        //comment handling
        else if(ch=='/')
        {
            char comment_next=fgetc(fp);

            //single line comment
            if(comment_next=='/')
            {
                while((ch=fgetc(fp))!=EOF && ch!='\n');
                continue;
            }

            //multi line comment
            else if(comment_next=='*')
            {
                char last=0;

                while((ch=fgetc(fp))!=EOF)
                {
                    if(last=='*' && ch=='/')
                    {
                        break;
                    }
                    last=ch;
                }
                continue;
            }

            //what if normal division operator
            else
            {
                fseek(fp,-1,SEEK_CUR); //move file ptr back

                tok.tok_str[0]='/';
                tok.tok_str[1]='\0';

                tok.type=OPERATOR;
                return tok; //returns / as operator token
            }
        }

        //operator
        else if(strchr(operators,ch))
        {
            tok.tok_str[0]=ch;
            tok.tok_str[1]='\0';

            tok.type=OPERATOR;
            return tok;
        }
    }
    return tok; //return UNKNOWN
}


//categorize the token
void categorizeToken(Token* token)
{
    //check keyword
    if(isKeyword(token->tok_str))
    {
        token->type=KEYWORD;
    }
    //check identifier
    else if(isIdentifier(token->tok_str))
    {
        token->type=IDENTIFIER;
    }
    //check operator
    else if(isOperator(token->tok_str))
    {
        token->type=OPERATOR;
    }
    //check specialCharacters
    else if(isSpecialCharacter(token->tok_str[0]))
    {
        token->type=SPECIAL_CHARACTER;
    }
    //check constant/literal
    else if(isConstant(token->tok_str))
    {
        token->type=CONSTANT;
    }
    //invalid token
    else
    {
        token->type=UNKNOWN;
    }
}

