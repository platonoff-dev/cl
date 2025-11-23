#ifndef CL_COMMON_H
#define CL_COMMON_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// Version information
#define CL_VERSION_MAJOR 0
#define CL_VERSION_MINOR 1
#define CL_VERSION_PATCH 0

// Common utility macros
#define CL_UNUSED(x) ((void)(x))
#define CL_ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Memory allocation helpers
#define CL_MALLOC(size) malloc(size)
#define CL_CALLOC(count, size) calloc(count, size)
#define CL_REALLOC(ptr, size) realloc(ptr, size)
#define CL_FREE(ptr) do { free(ptr); (ptr) = NULL; } while(0)

#endif // CL_COMMON_H
