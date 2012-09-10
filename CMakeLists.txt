#=================================
# CMake configuration
#=================================
cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules" )

#=================================
# Project information
#=================================
project( SQUIDGE C CXX )
set( SQUIDGE_VERSION_MAJOR 0 )
set( SQUIDGE_VERSION_MINOR 1 )

# setup where we dump executables, static/import libraries, and shared
# libraries/DLLs by default.
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${SQUIDGE_BINARY_DIR}/bin" )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${SQUIDGE_BINARY_DIR}/lib" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${SQUIDGE_BINARY_DIR}/bin" )

#=================================
# Setup dependencies
#=================================

find_package( SDL REQUIRED )
if( SDL_FOUND )
   message( STATUS "Found SDL" )
   message( STATUS "  Include: ${SDL_INCLUDE_DIR}" )
   message( STATUS "  Library: ${SDL_LIBRARY}" )
else()
   message( FATAL_ERROR "SDL not found!" )
endif()

find_package( SDL_image REQUIRED )

if( SDLIMAGE_FOUND )
   message( STATUS "Found SDL_image" )
   message( STATUS "  Include: ${SDLIMAGE_INCLUDE_DIR}" )
   message( STATUS "  Library: ${SDLIMAGE_LIBRARY}" )
else()
   message( FATAL_ERROR "SDL_image not found!" )
endif()

set( Boost_COMPILER "" )
set( Boost_USE_STATIC_LIBS ON )
set( Boost_USE_MULTITHREADED ON )
set( BOOST_USE_STATIC_RUNTIME OFF )

find_package( Boost 1.47 REQUIRED chrono system thread date_time random filesystem )

if( Boost_FOUND )
   message( STATUS "Found Boost" )
   message( STATUS "  Include: ${Boost_INCLUDE_DIRS}" )
   message( STATUS "  Library: ${Boost_LIBRARIES}" )
else()
   message( FATAL_ERROR "Boost not found!" )
endif()

find_package( OpenGL REQUIRED )

if( SQUIDGE_USE_OPENGL STREQUAL YES AND OPENGL_FOUND )
   message( STATUS "Found OpenGL" )
   message( STATUS "  Include: ${OPENGL_INCLUDE_DIR}" )
   message( STATUS "  Library: ${OPENGL_LIBRARIES}" )
endif()

#=================================
# Add vendor components
#=================================

add_subdirectory( vendor/gtest-1.6.0 )

#=================================
# Add component tests
#=================================
add_subdirectory( tests )

#================================
# Add the real components
#=================================
add_subdirectory( client )
#add_subdirectory( server )
