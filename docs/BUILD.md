# Building the CL Programming Language

## Prerequisites

- CMake 3.20 or higher
- A C23-compatible compiler (GCC 14+, Clang 18+, or MSVC 2022+)
- Make or Ninja build system

## Build Instructions

### Unix-like Systems (Linux, macOS)

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build
cmake --build .

# Run tests
ctest

# Install (optional)
sudo cmake --install .
```

### Windows (Visual Studio)

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake .. -G "Visual Studio 17 2022"

# Build
cmake --build . --config Release

# Run tests
ctest -C Release
```

## Build Types

- **Debug**: Includes debugging symbols, no optimization
  ```bash
  cmake .. -DCMAKE_BUILD_TYPE=Debug
  ```

- **Release**: Full optimization, no debugging symbols
  ```bash
  cmake .. -DCMAKE_BUILD_TYPE=Release
  ```

## Running the Compiler

After building, the `cl` executable will be in the `build` directory:

```bash
# Run REPL
./cl

# Compile a file
./cl myprogram.cl

# Show version
./cl --version

# Show help
./cl --help
```

## Development

### Code Formatting

The project uses clang-format for code formatting. Format all files with:

```bash
find src include tests -name "*.c" -o -name "*.h" | xargs clang-format -i
```

### Compiler Flags

The project uses strict compiler warnings to catch potential issues:
- `-Wall -Wextra -Wpedantic -Werror`
- Stack protection and security hardening flags
- Position-independent code (PIE)

### Testing

Tests are built automatically with the main project. Run them with:

```bash
cd build
ctest --output-on-failure
```

Or run individual tests:

```bash
./tests/test_lexer
./tests/test_parser
```

## Troubleshooting

### C23 not supported

If your compiler doesn't support C23, you can fall back to C17:
```bash
cmake .. -DCMAKE_C_STANDARD=17
```

### Compiler not found

Specify a different compiler:
```bash
cmake .. -DCMAKE_C_COMPILER=gcc-14
# or
cmake .. -DCMAKE_C_COMPILER=clang-18
```
