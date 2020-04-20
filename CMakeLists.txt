cmake_minimum_required(VERSION 3.5)

project(tetris CXX)

set(TETRIS_VERSION_MAJOR 0)
set(TETRIS_VERSION_MINOR 2)

OPTION ( DEFINE_DEBUG "Build the project with using debugging logs" OFF)


set (CMAKE_CXX_STANDARD 20)

if(CMAKE_CXX_COMPILER MATCHES ".*clang[+][+]" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    MESSAGE("Compiler CLANG")
    set (CMAKE_CXX_FLAGS_DEBUG " -O0 -fopenmp -g -Wall -Wextra -Wshadow -Wno-unused-parameter -Wnon-virtual-dtor ")
    set (CMAKE_CXX_FLAGS_RELEASE "-march=native -fopenmp -O3 -Wno-unused-parameter ")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    MESSAGE("Compiler GCC")
    set (CMAKE_CXX_FLAGS_DEBUG " -O0  -fopenmp -g -Wall -Wextra -Wshadow -Wno-unused-parameter -Wnon-virtual-dtor -fconcepts  ")
    set (CMAKE_CXX_FLAGS_RELEASE "-march=native -fopenmp -O3 -Wno-unused-parameter -fconcepts -Wall -Wextra -Wnon-virtual-dtor")
endif()
if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
    endif()
    set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
    add_definitions(-DTETRIS_WIN_32)
endif()

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install")

IF(DEFINE_DEBUG)
  MESSAGE("Adding Debug flag...")
  ADD_DEFINITIONS(-DDEBUG_TETRIS)
  SET(CMAKE_BUILD_TYPE Debug)
  MESSAGE("Build type is " ${CMAKE_BUILD_TYPE})
ENDIF(DEFINE_DEBUG)


configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/lib/inc/config.h"
  )
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_program(CCACHE_EXECUTABLE ccache)
mark_as_advanced(CCACHE_EXECUTABLE)
if(CCACHE_EXECUTABLE)
  foreach(LANG C CXX)
    if(NOT DEFINED CMAKE_${LANG}_COMPILER_LAUNCHER AND NOT CMAKE_${LANG}_COMPILER MATCHES ".*/ccache")
      message(STATUS "Enabling ccache for ${LANG}")
      set(CMAKE_${LANG}_COMPILER_LAUNCHER ${CCACHE_EXECUTABLE} CACHE STRING "")
    endif()
  endforeach()
endif()

set(EXECUTABLE_NAME "tetris")

include_directories( . )
include_directories( lib )
include_directories( lib/inc )

file( GLOB LIBRARY_SOURCE_FILES lib/src/*.cpp )
file( GLOB LIBRARY_HEADER_FILES lib/inc/*.hpp )




if(WIN32)
    add_executable(${EXECUTABLE_NAME} WIN32 driver/main.cpp ${LIBRARY_HEADER_FILES} ${LIBRARY_SOURCE_FILES})
    target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-audio sfml-main )
else()
    add_executable(${EXECUTABLE_NAME} driver/main.cpp ${LIBRARY_HEADER_FILES} ${LIBRARY_SOURCE_FILES})
    target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-audio )

endif()
