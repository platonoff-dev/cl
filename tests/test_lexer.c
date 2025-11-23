#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "common.h"
#include "lexer.h"

static void test_basic_tokens(void) {
    const char* source = "+ - * / ( ) { } , ;";
    Lexer lexer;
    lexer_init(&lexer, source);
    
    TokenType expected[] = {
        TOKEN_PLUS, TOKEN_MINUS, TOKEN_STAR, TOKEN_SLASH,
        TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_LBRACE, TOKEN_RBRACE,
        TOKEN_COMMA, TOKEN_SEMICOLON, TOKEN_EOF
    };
    
    for (size_t i = 0; i < sizeof(expected) / sizeof(expected[0]); i++) {
        Token token = lexer_next_token(&lexer);
        assert(token.type == expected[i]);
        CL_UNUSED(token);
    }
    
    printf("test_basic_tokens: PASSED\n");
}

static void test_numbers(void) {
    const char* source = "123 45.67 0.5";
    Lexer lexer;
    lexer_init(&lexer, source);
    
    Token token = lexer_next_token(&lexer);
    assert(token.type == TOKEN_NUMBER);
    assert(strncmp(token.start, "123", 3) == 0);
    
    token = lexer_next_token(&lexer);
    assert(token.type == TOKEN_NUMBER);
    assert(strncmp(token.start, "45.67", 5) == 0);
    
    token = lexer_next_token(&lexer);
    assert(token.type == TOKEN_NUMBER);
    assert(strncmp(token.start, "0.5", 3) == 0);
    
    CL_UNUSED(token);
    printf("test_numbers: PASSED\n");
}

static void test_identifiers_and_keywords(void) {
    const char* source = "let x if else while function return";
    Lexer lexer;
    lexer_init(&lexer, source);
    
    TokenType expected[] = {
        TOKEN_LET, TOKEN_IDENTIFIER, TOKEN_IF, TOKEN_ELSE,
        TOKEN_WHILE, TOKEN_FUNCTION, TOKEN_RETURN, TOKEN_EOF
    };
    
    for (size_t i = 0; i < sizeof(expected) / sizeof(expected[0]); i++) {
        Token token = lexer_next_token(&lexer);
        assert(token.type == expected[i]);
        CL_UNUSED(token);
    }
    
    printf("test_identifiers_and_keywords: PASSED\n");
}

static void test_strings(void) {
    const char* source = "\"hello\" \"world\"";
    Lexer lexer;
    lexer_init(&lexer, source);
    
    Token token = lexer_next_token(&lexer);
    assert(token.type == TOKEN_STRING);
    
    token = lexer_next_token(&lexer);
    assert(token.type == TOKEN_STRING);
    
    CL_UNUSED(token);
    printf("test_strings: PASSED\n");
}

static void test_operators(void) {
    const char* source = "== != < <= > >=";
    Lexer lexer;
    lexer_init(&lexer, source);
    
    TokenType expected[] = {
        TOKEN_EQUAL_EQUAL, TOKEN_BANG_EQUAL,
        TOKEN_LESS, TOKEN_LESS_EQUAL,
        TOKEN_GREATER, TOKEN_GREATER_EQUAL,
        TOKEN_EOF
    };
    
    for (size_t i = 0; i < sizeof(expected) / sizeof(expected[0]); i++) {
        Token token = lexer_next_token(&lexer);
        assert(token.type == expected[i]);
        CL_UNUSED(token);
    }
    
    printf("test_operators: PASSED\n");
}

static void test_comments(void) {
    const char* source = "let x // this is a comment\nlet y";
    Lexer lexer;
    lexer_init(&lexer, source);
    
    Token token = lexer_next_token(&lexer);
    assert(token.type == TOKEN_LET);
    
    token = lexer_next_token(&lexer);
    assert(token.type == TOKEN_IDENTIFIER);
    
    token = lexer_next_token(&lexer);
    assert(token.type == TOKEN_LET);
    
    token = lexer_next_token(&lexer);
    assert(token.type == TOKEN_IDENTIFIER);
    
    CL_UNUSED(token);
    printf("test_comments: PASSED\n");
}

int main(void) {
    printf("Running lexer tests...\n");
    
    test_basic_tokens();
    test_numbers();
    test_identifiers_and_keywords();
    test_strings();
    test_operators();
    test_comments();
    
    printf("\nAll lexer tests passed!\n");
    return 0;
}
