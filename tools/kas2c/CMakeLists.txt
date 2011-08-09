	SET(CMAKE_C_COMPILER "llvm-gcc")
	SET(CMAKE_C_OUTPUT_EXTENSION ".bc")
	SET(CMAKE_C_LINK_EXECUTABLE "llvm-ld")


find_package(FLEX REQUIRED)
FLEX_TARGET(MyScanner lexer.l ${CMAKE_CURRENT_SOURCE_DIR}/lexer.c)

find_package(BISON REQUIRED)
BISON_TARGET(MyParser parser.y ${CMAKE_CURRENT_SOURCE_DIR}/parser.c)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

#/usr/bin/lex -i -olexer.c lexer.l
#execute_process(COMMAND lex -i -olexer.c lexer.l)

#/usr/bin/yacc -d -o parser.c parser.y
#execute_process(COMMAND yacc -d -oparser.c parser.y)

SETUP_LLVM()
add_llvm_executable(kas2c ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS})


