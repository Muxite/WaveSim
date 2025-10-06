add_library(
	wave
	"display.cpp"
	"display.h"
	"world.cpp"
	"world.h"
	"function_generator.cpp"
	"function_generator.h"
	"benchmark.h"
	"benchmark.cpp"
)

set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "")
set(SFML_BUILD_TESTS OFF CACHE BOOL "")
set(SFML_BUILD_DOC OFF CACHE BOOL "")
set(SFML_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/sfml-build")
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/SFML" ${SFML_BINARY_DIR})

# expose directory to users of the library
target_include_directories(
	wave PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
	wave PUBLIC
	sfml-graphics
	sfml-window
	sfml-system
)
