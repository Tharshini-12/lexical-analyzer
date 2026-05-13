/* Name        : Tharshini S
   Date        : 12-05-2026
   File Name   : helper.c
   Description : Token Verification Helper Functions  */

#include "lexical_analyzer.h"

//access global variables from lexer.c
extern const char* keywords[MAX_KEYWORDS];
extern const char* operators;
extern const char* specialCharacters;

//check keyword
int isKeyword(const char* str)
{
    for(int i=0;i<MAX_KEYWORDS;i++)
    {
        if(strcmp(str,keywords[i])==0) //compare input string with keyword list
        {
            return 1;
        }
    }
    return 0;
}

//check operator
int isOperator(const char* str)
{
    //strchr check the chara is in operators string and strlen ensures only 1 char operator
    {
    if(strchr(operators,str[0]) && strlen(str)==1) 
        return 1;
    }
    return 0;
}

//check special character
int isSpecialCharacter(char ch)
{
    if(strchr(specialCharacters,ch)) //check character is exist in special characters list
    {
        return 1;
    }
    return 0;
}

//check constant/literal
int isConstant(const char* str)
{
    int i=0;
    //empty string check
    if (str[i]=='\0')
    {
        return 0;
    }

    int dot=0; //for counting decimal points
    while(str[i])
    {
        if(str[i]=='.') 
        {
            dot++;
        }
        else if(!is_digit(str[i])) //if not digit means invalid
        {
            return 0;
        }
        i++;
    }
    if(dot<=1) //only 1 decimal point should exist otherwise invalid
    {
        return 1;
    }
    return 0;   

}

//check identifier
int isIdentifier(const char* str)
{
    //check 1st character
    if(!(is_alpha(str[0])||str[0]=='_')) //first character must be alphabets or underscore
    {
        return 0;
    }

    //check remaining chars
    for(int i=1;str[i]!='\0';i++)
    {
        if(!(is_alnum(str[i]) || str[i]=='_'))//remaining characters can be alphabets, digits or underscore
        {
            return 0;
        }
    }
    return 1;
}

//function to check alphabet
int is_alpha(char ch)
{
    if(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z')
    {
        return 1;
    }
    return 0;
}

//function to check digit
int is_digit(int num)
{
    if(num>='0'&&num<='9')
    {
        return 1;
    }
    return 0;
}

//function to check alphanumeric characters
int is_alnum(char ch)
{
    if(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z'||ch>='0'&&ch<='9')
    {
        return 1;
    }
    return 0;
}
