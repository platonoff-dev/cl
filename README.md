# CL Programming Language

A modern programming language implementation in C23.

## Features

- **Modern C23**: Built using the newest C standard for improved safety and features
- **Lexer & Parser**: Complete tokenization and parsing infrastructure
- **AST**: Abstract Syntax Tree representation for code analysis
- **REPL**: Interactive Read-Eval-Print Loop for experimentation
- **Type-safe**: Strong type checking and error handling
- **Well-tested**: Comprehensive test suite using CMake/CTest

## Quick Start

### Building

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Running

```bash
# Start REPL
./cl

# Run a file
./cl myprogram.cl

# Show help
./cl --help
```

### Example

```bash
$ ./cl
cl REPL v0.1.0
Press Ctrl+D to exit

> 2 + 3 * 4
Token: NUMBER '2'
Token: PLUS
Token: NUMBER '3'
Token: STAR
Token: NUMBER '4'
Token: EOF
```

## Documentation

- [Build Instructions](docs/BUILD.md)
- [Contributing Guide](docs/CONTRIBUTING.md)

## Project Structure

```
cl/
├── src/           # Source files
│   ├── main.c     # Entry point
│   ├── lexer.c    # Lexical analyzer
│   ├── parser.c   # Parser
│   ├── ast.c      # Abstract Syntax Tree
│   └── error.c    # Error reporting
├── include/       # Header files
├── tests/         # Test suite
├── docs/          # Documentation
└── CMakeLists.txt # Build configuration
```

## Requirements

- CMake 3.20+
- C23-compatible compiler (GCC 14+, Clang 18+, or MSVC 2022+)

## License

This project is open source.

## Contributing

See [CONTRIBUTING.md](docs/CONTRIBUTING.md) for guidelines.