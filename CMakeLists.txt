cmake_minimum_required(VERSION 2.8)
project(dami)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${dami_SOURCE_DIR}/include ${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(
	dami
	${dami_SOURCE_DIR}/src/main.c
	${dami_SOURCE_DIR}/src/tokenizer.c
	${dami_SOURCE_DIR}/src/stack.c
	${dami_SOURCE_DIR}/src/parser.c
	${dami_SOURCE_DIR}/src/ast.c
)

install(TARGETS dami DESTINATION bin)
