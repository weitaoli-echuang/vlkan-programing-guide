cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(VERSION 2.8)

#for ycm
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(NAME vulkan-programing-guide)

project(${NAME})

include_directories(base)

find_path(VULKAN_DIR NAMES vulkan/vulkan.h)
include_directories(${VULKAN_DIR})

find_library(VULKAN_LIB NAMES vulkan-1 vulkan)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_WIN32_KHR")

message(STATUS ${VULKAN_LIB})
message(STATUS ${VULKAN_DIR})

# Set preprocessor defines
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOMINMAX -D_USE_MATH_DEFINES")

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-std=c++14)
add_definitions(-std=c++0x)
add_definitions(-std=gnu++14)

#file(GLOB SOURCE *.cpp base/*.cpp)

# Function for building single example
function(buildExample EXAMPLE_NAME)
	file(GLOB SOURCE *.cpp base/*.cpp ${EXAMPLE_NAME}/*.cpp)
	#Window
	#add_executable(${EXAMPLE_NAME} WIN32 ${EXAMPLE_NAME}/${EXAMPLE_NAME}.cpp ${SOURCE})
	#Consle
	add_executable(${EXAMPLE_NAME} ${EXAMPLE_NAME}/${EXAMPLE_NAME}.cpp ${SOURCE})
	target_link_libraries(${EXAMPLE_NAME} ${VULKAN_LIB} ${ASSIMP_LIBRARIES} ${WINLIBS})
endfunction(buildExample)

# Build all examples
function(buildExamples)
	foreach(EXAMPLE ${EXAMPLES})
		buildExample(${EXAMPLE})
	endforeach(EXAMPLE)
endfunction(buildExamples)

# Compiler specific stuff
IF(MSVC)
    SET(CMAKE_CXX_FLAGS "/EHsc")
ENDIF(MSVC)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

set(EXAMPLES
	overview-of-vulkan
	MemoryAndResources
	queueAndCommands
	)

buildExamples()
