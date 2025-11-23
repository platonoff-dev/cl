#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ast.h"

ASTNode* ast_create_number(double value, size_t line, size_t column) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (node == NULL) return NULL;
    
    node->type = AST_NUMBER;
    node->line = line;
    node->column = column;
    node->data.number = value;
    return node;
}

ASTNode* ast_create_identifier(const char* name, size_t line, size_t column) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (node == NULL) return NULL;
    
    node->type = AST_IDENTIFIER;
    node->line = line;
    node->column = column;
    node->data.identifier = strdup(name);
    return node;
}

ASTNode* ast_create_binary_op(TokenType op, ASTNode* left, ASTNode* right, 
                              size_t line, size_t column) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (node == NULL) return NULL;
    
    node->type = AST_BINARY_OP;
    node->line = line;
    node->column = column;
    node->data.binary_op.op = op;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    return node;
}

void ast_free(ASTNode* node) {
    if (node == NULL) return;
    
    switch (node->type) {
        case AST_IDENTIFIER:
            free(node->data.identifier);
            break;
        case AST_BINARY_OP:
            ast_free(node->data.binary_op.left);
            ast_free(node->data.binary_op.right);
            break;
        case AST_UNARY_OP:
            ast_free(node->data.unary_op.operand);
            break;
        default:
            break;
    }
    
    free(node);
}

static void print_indent(int indent) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
}

void ast_print(const ASTNode* node, int indent) {
    if (node == NULL) {
        print_indent(indent);
        printf("<null>\n");
        return;
    }
    
    print_indent(indent);
    
    switch (node->type) {
        case AST_PROGRAM:
            printf("Program\n");
            break;
        case AST_NUMBER:
            printf("Number: %g\n", node->data.number);
            break;
        case AST_IDENTIFIER:
            printf("Identifier: %s\n", node->data.identifier);
            break;
        case AST_BINARY_OP:
            printf("BinaryOp: %s\n", token_type_to_string(node->data.binary_op.op));
            ast_print(node->data.binary_op.left, indent + 1);
            ast_print(node->data.binary_op.right, indent + 1);
            break;
        case AST_UNARY_OP:
            printf("UnaryOp: %s\n", token_type_to_string(node->data.unary_op.op));
            ast_print(node->data.unary_op.operand, indent + 1);
            break;
        default:
            printf("Unknown node type\n");
            break;
    }
}
