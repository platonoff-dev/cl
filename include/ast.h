#ifndef CL_AST_H
#define CL_AST_H

#include "common.h"
#include "lexer.h"

// AST node types
typedef enum {
    AST_PROGRAM,
    AST_NUMBER,
    AST_IDENTIFIER,
    AST_BINARY_OP,
    AST_UNARY_OP,
    AST_FUNCTION_CALL,
    AST_IF_STATEMENT,
    AST_WHILE_LOOP,
    AST_RETURN_STATEMENT,
} ASTNodeType;

// Forward declaration
typedef struct ASTNode ASTNode;

// Binary operator node
typedef struct {
    TokenType op;
    ASTNode* left;
    ASTNode* right;
} BinaryOpNode;

// Unary operator node
typedef struct {
    TokenType op;
    ASTNode* operand;
} UnaryOpNode;

// AST node structure
struct ASTNode {
    ASTNodeType type;
    size_t line;
    size_t column;
    union {
        double number;
        char* identifier;
        BinaryOpNode binary_op;
        UnaryOpNode unary_op;
    } data;
};

// AST functions
ASTNode* ast_create_number(double value, size_t line, size_t column);
ASTNode* ast_create_identifier(const char* name, size_t line, size_t column);
ASTNode* ast_create_binary_op(TokenType op, ASTNode* left, ASTNode* right, size_t line, size_t column);
void ast_free(ASTNode* node);
void ast_print(const ASTNode* node, int indent);

#endif // CL_AST_H
