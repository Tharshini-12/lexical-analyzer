/* Name        : Tharshini S
   Date        : 12-05-2026
   File Name   : lexical_analyzer.h
   Title       : Lexical Analyzer header file */

#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#define MAX_KEYWORDS 20 //maximum number of keywords
#define MAX_TOKEN_SIZE 100 //maximum size of token string

#include <stdio.h>
#include <string.h>

//enum for different token types
typedef enum {
    KEYWORD, 
    OPERATOR,
    SPECIAL_CHARACTER,
    CONSTANT,
    IDENTIFIER,
    UNKNOWN
} TokenType;

//structure to store token information
typedef struct {
    char tok_str[MAX_TOKEN_SIZE]; //stores actual token eg:"int" "char" "10"
    TokenType type; //stores token type eg:KEYWORD, OPERATOR..
} Token; //new datatype

//function declarations
void initializeLexer(const char* filename); 
Token getNextToken();
void categorizeToken(Token* token);

//helper functions
int isKeyword(const char* str);
int isOperator(const char* str);
int isSpecialCharacter(char ch);
int isConstant(const char* str);
int isIdentifier(const char* str);

int is_alnum(char ch);
int is_alpha(char ch);
int is_digit(int num);

#endif
