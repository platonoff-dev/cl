cmake_minimum_required(VERSION 3.20)

# Test executable
add_executable(test_lexer test_lexer.c ../src/lexer.c ../src/error.c)
target_include_directories(test_lexer PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_executable(test_parser 
    test_parser.c 
    ../src/lexer.c 
    ../src/parser.c 
    ../src/ast.c 
    ../src/error.c
)
target_include_directories(test_parser PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Add tests
add_test(NAME LexerTest COMMAND test_lexer)
add_test(NAME ParserTest COMMAND test_parser)
