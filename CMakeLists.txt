# -*-mode:cmake;coding:utf-8;tab-width:4;indent-tabs-mode:nil;-*- vim:ts=4:sw=4:expandtab:autoindent:enc=utf-8:
#
# The MIT License
#
# Copyright (c) 2008, 2009 Flusspferd contributors (see "CONTRIBUTORS" or
#                                      http://flusspferd.org/contributors.txt)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

project(Flusspferd_SDL)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

if(NOT CMAKE_BUILD_TYPE)
    set(
        CMAKE_BUILD_TYPE
        Debug
        CACHE
        STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif()

message(STATUS "Source: ${CMAKE_SOURCE_DIR}")
message(STATUS "Binary: ${CMAKE_BINARY_DIR}")

if(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files that cmake just created:\nrm -rf CMakeCache.txt CMakeFiles")
endif()

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(INSTALL_EXECUTABLES_PATH ${CMAKE_INSTALL_PREFIX}/bin)
set(INSTALL_LIBRARIES_PATH ${CMAKE_INSTALL_PREFIX}/lib)
set(INSTALL_LIBDATA_PATH ${CMAKE_INSTALL_PREFIX}/lib/flusspferd)
set(INSTALL_MODULES_PATH ${CMAKE_INSTALL_PREFIX}/lib/flusspferd/modules)
set(INSTALL_HEADERS_PATH ${CMAKE_INSTALL_PREFIX}/include)
set(INSTALL_ETC_PATH ${CMAKE_INSTALL_PREFIX}/etc)

add_definitions("-DINSTALL_PREFIX=\"${CMAKE_INSTALL_PREFIX}\"")

set(CMAKE_SHARED_MODULE_SUFFIX ${CMAKE_SHARED_LIBRARY_SUFFIX})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions("-DDEBUG")
endif()

#############################################################################

include(CheckIncludeFile)
include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(CheckCXXSourceRuns)
include(FindPkgConfig)

## Compiler options #########################################################

if(CMAKE_COMPILER_IS_GNUCXX)
    # MinGW doesn't set this by default
    if(WIN32)
        add_definitions(-DWIN32)
    endif()

    option(ENABLE_DEBUG_WARNINGS "Enable -Wpadded and -Weffc++" OFF)

    add_definitions("-pedantic-errors -Wall -Wextra"
    "-Winit-self -Woverloaded-virtual -Wnon-virtual-dtor -Wsign-promo")

    if (NOT WIN32)
        # Boost 1.39 on mingw seems to produce a lot of these - they are very
        # noisy
        add_definitions("-Wstrict-aliasing=1")
    endif()

    if(ENABLE_DEBUG_WARNINGS)
        add_definitions("-Wpadded -Weffc++")
    endif()

    add_definitions(-DBOOST_FILESYSTEM_NO_DEPRECATED)

    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")

    add_definitions("-Wno-long-long -ansi")

    set(CMAKE_REQUIRED_FLAGS "")

    check_cxx_source_compiles(
        "#if __GNUC__ < 4
        #error \"GCC too old\"
        #endif
        int main() {}"
        GCC_VERSION_OK)

    if(NOT GCC_VERSION_OK)
        message(FATAL_ERROR "GCC Version too old! Get a newer GCC.")
    endif()
elseif(MSVC)
    add_definitions("/W3 /wd4512 /wd4355 /wd4800 /wd4996 /wd4714 /EHa")
    set(WINLIBS projects/windows/lib32)
    set(WININCLUDES ${CMAKE_SOURCE_DIR}/${WINLIBS})
endif()

## Boost ####################################################################

set(Boost_USE_MULTITHREADED ON)

if(WIN32)
    set(Boost_USE_STATIC_LIBS ON)
endif()

set(Boost_FIND_REQUIRED TRUE)

find_package(Boost 1.40.0)

if(Boost_INCLUDE_DIR)
    include_directories(${Boost_INCLUDE_DIR})
else()
    message(FATAL_ERROR "Boost headers not found. You will have to specify them in your build environment or you can use -DBOOST_ROOT or -DBOOST_INCLUDE_DIR to tell cmake where your boost installation is.")
endif()

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found!")
endif()

set(BOOST_PARAMETER_MAX_ARITY "-DBOOST_PARAMETER_MAX_ARITY=10")
add_definitions(${BOOST_PARAMETER_MAX_ARITY})

## SDL ######################################################################

find_package(SDL)

if(NOT SDL_FOUND)
  message(FATAL_ERROR "SDL not found")
endif()

set(SDL_LIBRARIES ${SDL_LIBRARY})
include_directories(${SDL_INCLUDE_DIR})

## Flusspferd ##############################################################

find_package(Flusspferd)

if(NOT FLUSSPFERD_FOUND)
  message(FATAL_ERROR "Flusspferd not found")
endif()

include_directories(${Flusspferd_INCLUDE_DIR})

## Build ###################################################################

file(GLOB
  SDL_sources
  ${Flusspferd_SDL_SOURCE_DIR}/src/*.cpp
  ${Flusspferd_SDL_SOURCE_DIR}/src/*.hpp)

# OSX doesn't work properly with this as MODULE (something about --flat-namespace)
if (APPLE)
  add_library(SDL_PLUGIN SHARED ${SDL_sources})
else()
  add_library(SDL_PLUGIN MODULE ${SDL_sources})
endif()

set_property(
  TARGET SDL_PLUGIN
  PROPERTY OUTPUT_NAME
  sdl)

set_property(
  TARGET SDL_PLUGIN
  PROPERTY DEFINITIONS
  ${SDL_DEFINITIONS})

IF (WIN32)
  # Remove the 'lib' prefix from plugin modules on win32
  set_property(
    TARGET SDL_PLUGIN
    PROPERTY PREFIX "")
ENDIF()

target_link_libraries(
  SDL_PLUGIN
  ${Flusspferd_LIBRARY}
  ${SDL_LIBRARIES})

install(TARGETS
  SDL_PLUGIN
  LIBRARY DESTINATION ${INSTALL_MODULES_PATH})

## Headers ##################################################################

file(GLOB_RECURSE HEADERFILES *.hpp)

foreach(HEADER ${HEADERFILES})
  set_source_files_properties(${HEADER}
    PROPERTIES
    HEADER_FILE_ONLY TRUE)
endforeach()

message(STATUS "Configuration SUCCESSFUL. No fatal errors.")
