#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "error.h"

static void print_version(void) {
    printf("cl version %d.%d.%d\n", 
           CL_VERSION_MAJOR, 
           CL_VERSION_MINOR, 
           CL_VERSION_PATCH);
}

static void print_usage(const char* program_name) {
    printf("Usage: %s [options] <file>\n", program_name);
    printf("Options:\n");
    printf("  -h, --help     Show this help message\n");
    printf("  -v, --version  Show version information\n");
}

static char* read_file(const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file '%s'\n", path);
        return NULL;
    }
    
    fseek(file, 0L, SEEK_END);
    size_t file_size = (size_t)ftell(file);
    rewind(file);
    
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Not enough memory to read '%s'\n", path);
        fclose(file);
        return NULL;
    }
    
    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
    if (bytes_read < file_size) {
        fprintf(stderr, "Error: Could not read file '%s'\n", path);
        free(buffer);
        fclose(file);
        return NULL;
    }
    
    buffer[bytes_read] = '\0';
    fclose(file);
    return buffer;
}

static int run_file(const char* path) {
    char* source = read_file(path);
    if (source == NULL) {
        return 74; // EX_IOERR
    }
    
    Lexer lexer;
    lexer_init(&lexer, source);
    
    Parser parser;
    parser_init(&parser, &lexer);
    
    ASTNode* ast = parser_parse(&parser);
    
    if (ast != NULL) {
        printf("Parsing successful!\n");
        ast_print(ast, 0);
        ast_free(ast);
    }
    
    parser_free(&parser);
    free(source);
    
    return 0;
}

static int run_repl(void) {
    char line[1024];
    
    printf("cl REPL v%d.%d.%d\n", 
           CL_VERSION_MAJOR, 
           CL_VERSION_MINOR, 
           CL_VERSION_PATCH);
    printf("Press Ctrl+D to exit\n\n");
    
    while (true) {
        printf("> ");
        
        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }
        
        Lexer lexer;
        lexer_init(&lexer, line);
        
        Token token;
        do {
            token = lexer_next_token(&lexer);
            printf("Token: %s", token_type_to_string(token.type));
            if (token.type == TOKEN_IDENTIFIER || token.type == TOKEN_NUMBER) {
                printf(" '%.*s'", (int)token.length, token.start);
            }
            printf("\n");
        } while (token.type != TOKEN_EOF && token.type != TOKEN_ERROR);
    }
    
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        return run_repl();
    }
    
    if (argc == 2) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        }
        if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
            print_version();
            return 0;
        }
        return run_file(argv[1]);
    }
    
    print_usage(argv[0]);
    return 64; // EX_USAGE
}
