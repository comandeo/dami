cmake_minimum_required(VERSION 3.15)
project(dami)

#find_package(LLVM REQUIRED CONFIG)
#message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
#message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
#include_directories(${dami_SOURCE_DIR}/include ${LLVM_INCLUDE_DIRS})
#add_definitions(${LLVM_DEFINITIONS})

include_directories(${dami_SOURCE_DIR}/include)

add_executable(
	dami
	${dami_SOURCE_DIR}/src/main.cpp
	${dami_SOURCE_DIR}/src/tokenizer.cpp
	${dami_SOURCE_DIR}/src/parser.cpp
	${dami_SOURCE_DIR}/src/ast.cpp
	${dami_SOURCE_DIR}/src/interpreter.cpp
	${dami_SOURCE_DIR}/src/value.cpp
)

install(TARGETS dami DESTINATION bin)
