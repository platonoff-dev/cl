#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "error.h"

static char* string_duplicate(const char* str, size_t len) {
    char* result = (char*)malloc(len + 1);
    if (result == NULL) return NULL;
    memcpy(result, str, len);
    result[len] = '\0';
    return result;
}

void parser_init(Parser* parser, Lexer* lexer) {
    parser->lexer = lexer;
    parser->had_error = false;
    parser->panic_mode = false;
    
    // Initialize with first token
    parser->current = lexer_next_token(lexer);
}

void parser_free(Parser* parser) {
    CL_UNUSED(parser);
    // Nothing to free for now
}

static void advance(Parser* parser) {
    parser->previous = parser->current;
    
    while (true) {
        parser->current = lexer_next_token(parser->lexer);
        if (parser->current.type != TOKEN_ERROR) break;
        
        error_report_at_token(ERROR_ERROR, &parser->current, 
                            "%.*s", (int)parser->current.length, parser->current.start);
        parser->had_error = true;
    }
}

static bool check(const Parser* parser, TokenType type) {
    return parser->current.type == type;
}

static bool match(Parser* parser, TokenType type) {
    if (!check(parser, type)) return false;
    advance(parser);
    return true;
}

static void consume(Parser* parser, TokenType type, const char* message) {
    if (parser->current.type == type) {
        advance(parser);
        return;
    }
    
    error_report_at_token(ERROR_ERROR, &parser->current, "%s", message);
    parser->had_error = true;
}

// Forward declarations for recursive descent parser
static ASTNode* expression(Parser* parser);
static ASTNode* primary(Parser* parser);

static ASTNode* primary(Parser* parser) {
    if (match(parser, TOKEN_NUMBER)) {
        char* end;
        double value = strtod(parser->previous.start, &end);
        return ast_create_number(value, parser->previous.line, parser->previous.column);
    }
    
    if (match(parser, TOKEN_IDENTIFIER)) {
        char* name = string_duplicate(parser->previous.start, parser->previous.length);
        return ast_create_identifier(name, parser->previous.line, parser->previous.column);
    }
    
    if (match(parser, TOKEN_LPAREN)) {
        ASTNode* expr = expression(parser);
        consume(parser, TOKEN_RPAREN, "Expected ')' after expression");
        return expr;
    }
    
    error_report_at_token(ERROR_ERROR, &parser->current, "Expected expression");
    parser->had_error = true;
    return NULL;
}

static ASTNode* unary(Parser* parser) {
    if (match(parser, TOKEN_MINUS) || match(parser, TOKEN_BANG)) {
        Token op = parser->previous;
        ASTNode* operand = unary(parser);
        
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = AST_UNARY_OP;
        node->line = op.line;
        node->column = op.column;
        node->data.unary_op.op = op.type;
        node->data.unary_op.operand = operand;
        return node;
    }
    
    return primary(parser);
}

static ASTNode* factor(Parser* parser) {
    ASTNode* node = unary(parser);
    
    while (match(parser, TOKEN_STAR) || match(parser, TOKEN_SLASH)) {
        Token op = parser->previous;
        ASTNode* right = unary(parser);
        node = ast_create_binary_op(op.type, node, right, op.line, op.column);
    }
    
    return node;
}

static ASTNode* term(Parser* parser) {
    ASTNode* node = factor(parser);
    
    while (match(parser, TOKEN_PLUS) || match(parser, TOKEN_MINUS)) {
        Token op = parser->previous;
        ASTNode* right = factor(parser);
        node = ast_create_binary_op(op.type, node, right, op.line, op.column);
    }
    
    return node;
}

static ASTNode* comparison(Parser* parser) {
    ASTNode* node = term(parser);
    
    while (match(parser, TOKEN_LESS) || match(parser, TOKEN_LESS_EQUAL) ||
           match(parser, TOKEN_GREATER) || match(parser, TOKEN_GREATER_EQUAL)) {
        Token op = parser->previous;
        ASTNode* right = term(parser);
        node = ast_create_binary_op(op.type, node, right, op.line, op.column);
    }
    
    return node;
}

static ASTNode* equality(Parser* parser) {
    ASTNode* node = comparison(parser);
    
    while (match(parser, TOKEN_EQUAL_EQUAL) || match(parser, TOKEN_BANG_EQUAL)) {
        Token op = parser->previous;
        ASTNode* right = comparison(parser);
        node = ast_create_binary_op(op.type, node, right, op.line, op.column);
    }
    
    return node;
}

static ASTNode* expression(Parser* parser) {
    return equality(parser);
}

ASTNode* parser_parse(Parser* parser) {
    if (parser->current.type == TOKEN_EOF) {
        return NULL;
    }
    
    ASTNode* result = expression(parser);
    
    if (parser->had_error) {
        ast_free(result);
        return NULL;
    }
    
    return result;
}
