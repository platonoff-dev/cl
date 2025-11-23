# Contributing to CL

Thank you for your interest in contributing to the CL programming language!

## Development Setup

1. Fork the repository
2. Clone your fork: `git clone https://github.com/YOUR_USERNAME/cl.git`
3. Create a feature branch: `git checkout -b feature/my-feature`
4. Make your changes
5. Run tests: `cd build && ctest`
6. Commit your changes: `git commit -am 'Add my feature'`
7. Push to the branch: `git push origin feature/my-feature`
8. Create a Pull Request

## Code Style

This project follows these coding standards:

### C Code Style

- Use C23 standard features where appropriate
- Follow the existing code style (use clang-format)
- Use 4 spaces for indentation (no tabs)
- Maximum line length: 100 characters
- Use snake_case for functions and variables
- Use PascalCase for types and structs
- Use UPPER_CASE for constants and macros

### Naming Conventions

- Header guards: `CL_MODULENAME_H`
- Function names: `module_function_name()`
- Type names: `ModuleName` or `ModuleNameType`
- Enum values: `MODULE_VALUE_NAME`

### Comments

- Use `//` for single-line comments
- Use `/* */` for multi-line comments
- Document all public API functions
- Explain complex algorithms

### Example

```c
#ifndef CL_EXAMPLE_H
#define CL_EXAMPLE_H

#include "common.h"

// This is a single-line comment

/*
 * This is a multi-line comment
 * explaining a complex function
 */
typedef struct {
    int value;
    char* name;
} ExampleStruct;

// Initialize an example structure
void example_init(ExampleStruct* example, int value);

// Free resources used by example
void example_free(ExampleStruct* example);

#endif // CL_EXAMPLE_H
```

## Testing

- Write tests for all new features
- Ensure all tests pass before submitting a PR
- Aim for high code coverage
- Test edge cases and error conditions

## Documentation

- Update documentation for any user-facing changes
- Add comments for complex code sections
- Update BUILD.md if build process changes
- Update README.md for significant features

## Commit Messages

Follow the conventional commits format:

- `feat: Add new feature`
- `fix: Fix bug in parser`
- `docs: Update documentation`
- `test: Add tests for lexer`
- `refactor: Refactor AST module`
- `style: Format code`
- `chore: Update build system`

## Pull Request Process

1. Ensure all tests pass
2. Update documentation as needed
3. Follow the code style guidelines
4. Write a clear PR description
5. Link any related issues
6. Wait for review and address feedback

## Questions?

Feel free to open an issue for any questions or concerns!
