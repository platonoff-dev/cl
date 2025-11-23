#ifndef CL_ERROR_H
#define CL_ERROR_H

#include "common.h"
#include "lexer.h"

// Error severity levels
typedef enum {
    ERROR_WARNING,
    ERROR_ERROR,
    ERROR_FATAL,
} ErrorLevel;

// Error reporting functions
void error_report(ErrorLevel level, size_t line, size_t column, const char* format, ...)
    __attribute__((format(printf, 4, 5)));
void error_report_at_token(ErrorLevel level, const Token* token, const char* format, ...)
    __attribute__((format(printf, 3, 4)));

#endif // CL_ERROR_H
