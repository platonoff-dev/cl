#ifndef CL_LEXER_H
#define CL_LEXER_H

#include "common.h"

// Token types
typedef enum {
    TOKEN_EOF,
    TOKEN_ERROR,
    
    // Literals
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,
    
    // Keywords
    TOKEN_LET,
    TOKEN_FUNCTION,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_RETURN,
    
    // Operators
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_EQUAL,
    TOKEN_EQUAL_EQUAL,
    TOKEN_BANG,
    TOKEN_BANG_EQUAL,
    TOKEN_LESS,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER,
    TOKEN_GREATER_EQUAL,
    
    // Punctuation
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_COMMA,
    TOKEN_SEMICOLON,
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    const char* start;
    size_t length;
    size_t line;
    size_t column;
} Token;

// Lexer structure
typedef struct {
    const char* source;
    const char* start;
    const char* current;
    size_t line;
    size_t column;
} Lexer;

// Lexer functions
void lexer_init(Lexer* lexer, const char* source);
Token lexer_next_token(Lexer* lexer);
const char* token_type_to_string(TokenType type);

#endif // CL_LEXER_H
