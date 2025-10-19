cmake_policy(SET CMP0104 NEW)

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
	"calculate_wave_cuda.h"
	"calculate_wave_cuda.cu"
)

set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "")
set(SFML_BUILD_TESTS OFF CACHE BOOL "")
set(SFML_BUILD_DOC OFF CACHE BOOL "")
set(SFML_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/sfml-build")
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/SFML" ${SFML_BINARY_DIR})

set_target_properties(
	wave PROPERTIES 
	CUDA_SEPARABLE_COMPILATION ON
)

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
