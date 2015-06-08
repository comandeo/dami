cmake_minimum_required(VERSION 2.8)
project(dami)

include_directories(${dami_SOURCE_DIR}/include)

add_executable(
	dami
	${dami_SOURCE_DIR}/src/main.c
	${dami_SOURCE_DIR}/src/tokenizer.c
	${dami_SOURCE_DIR}/src/stack.c
	${dami_SOURCE_DIR}/src/parser.c
)

install(TARGETS dami DESTINATION bin)
