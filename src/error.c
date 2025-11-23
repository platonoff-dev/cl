#include <stdio.h>
#include <stdarg.h>
#include "error.h"
#include "lexer.h"

static const char* error_level_to_string(ErrorLevel level) {
    switch (level) {
        case ERROR_WARNING: return "Warning";
        case ERROR_ERROR: return "Error";
        case ERROR_FATAL: return "Fatal";
        default: return "Unknown";
    }
}

void error_report(ErrorLevel level, size_t line, size_t column, const char* format, ...) {
    fprintf(stderr, "[%s at %zu:%zu] ", error_level_to_string(level), line, column);
    
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    
    fprintf(stderr, "\n");
}

void error_report_at_token(ErrorLevel level, const Token* token, const char* format, ...) {
    fprintf(stderr, "[%s at %zu:%zu] ", 
            error_level_to_string(level), 
            token->line, 
            token->column);
    
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    
    fprintf(stderr, "\n");
}
