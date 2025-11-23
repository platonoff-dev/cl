#ifndef CL_PARSER_H
#define CL_PARSER_H

#include "common.h"
#include "lexer.h"
#include "ast.h"

// Parser structure
typedef struct {
    Lexer* lexer;
    Token current;
    Token previous;
    bool had_error;
    bool panic_mode;
} Parser;

// Parser functions
void parser_init(Parser* parser, Lexer* lexer);
ASTNode* parser_parse(Parser* parser);
void parser_free(Parser* parser);

#endif // CL_PARSER_H
