#include <stdio.h>
#include <assert.h>
#include "common.h"
#include "parser.h"
#include "lexer.h"
#include "ast.h"

static void test_parse_number(void) {
    const char* source = "42";
    Lexer lexer;
    lexer_init(&lexer, source);
    
    Parser parser;
    parser_init(&parser, &lexer);
    
    ASTNode* ast = parser_parse(&parser);
    assert(ast != NULL);
    assert(ast->type == AST_NUMBER);
    assert(ast->data.number == 42.0);
    
    ast_free(ast);
    parser_free(&parser);
    
    printf("test_parse_number: PASSED\n");
}

static void test_parse_identifier(void) {
    const char* source = "myvar";
    Lexer lexer;
    lexer_init(&lexer, source);
    
    Parser parser;
    parser_init(&parser, &lexer);
    
    ASTNode* ast = parser_parse(&parser);
    assert(ast != NULL);
    assert(ast->type == AST_IDENTIFIER);
    
    ast_free(ast);
    parser_free(&parser);
    
    printf("test_parse_identifier: PASSED\n");
}

static void test_parse_binary_op(void) {
    const char* source = "2 + 3";
    Lexer lexer;
    lexer_init(&lexer, source);
    
    Parser parser;
    parser_init(&parser, &lexer);
    
    ASTNode* ast = parser_parse(&parser);
    assert(ast != NULL);
    assert(ast->type == AST_BINARY_OP);
    assert(ast->data.binary_op.op == TOKEN_PLUS);
    assert(ast->data.binary_op.left->type == AST_NUMBER);
    assert(ast->data.binary_op.right->type == AST_NUMBER);
    
    ast_free(ast);
    parser_free(&parser);
    
    printf("test_parse_binary_op: PASSED\n");
}

static void test_parse_precedence(void) {
    const char* source = "2 + 3 * 4";
    Lexer lexer;
    lexer_init(&lexer, source);
    
    Parser parser;
    parser_init(&parser, &lexer);
    
    ASTNode* ast = parser_parse(&parser);
    assert(ast != NULL);
    assert(ast->type == AST_BINARY_OP);
    assert(ast->data.binary_op.op == TOKEN_PLUS);
    
    // Right side should be 3 * 4
    ASTNode* right = ast->data.binary_op.right;
    assert(right->type == AST_BINARY_OP);
    assert(right->data.binary_op.op == TOKEN_STAR);
    
    CL_UNUSED(right);
    ast_free(ast);
    parser_free(&parser);
    
    printf("test_parse_precedence: PASSED\n");
}

static void test_parse_parentheses(void) {
    const char* source = "(2 + 3) * 4";
    Lexer lexer;
    lexer_init(&lexer, source);
    
    Parser parser;
    parser_init(&parser, &lexer);
    
    ASTNode* ast = parser_parse(&parser);
    assert(ast != NULL);
    assert(ast->type == AST_BINARY_OP);
    assert(ast->data.binary_op.op == TOKEN_STAR);
    
    // Left side should be 2 + 3
    ASTNode* left = ast->data.binary_op.left;
    assert(left->type == AST_BINARY_OP);
    assert(left->data.binary_op.op == TOKEN_PLUS);
    
    CL_UNUSED(left);
    ast_free(ast);
    parser_free(&parser);
    
    printf("test_parse_parentheses: PASSED\n");
}

int main(void) {
    printf("Running parser tests...\n");
    
    test_parse_number();
    test_parse_identifier();
    test_parse_binary_op();
    test_parse_precedence();
    test_parse_parentheses();
    
    printf("\nAll parser tests passed!\n");
    return 0;
}
