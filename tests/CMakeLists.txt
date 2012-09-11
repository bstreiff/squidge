#=================================
# List all the source files for SQUIDGETEST
#=================================
set( SQUIDGETEST_SOURCE_FILES
    "${SQUIDGE_SOURCE_DIR}/tests/RectangleTest.cpp"
    "${SQUIDGE_SOURCE_DIR}/tests/VectorTest.cpp"
    "${SQUIDGE_SOURCE_DIR}/tests/PointIteratorTest.cpp"
    "${SQUIDGE_SOURCE_DIR}/tests/CartographTest.cpp"
   )

set( SQUIDGETEST_OSX_SOURCE_FILES
   )

set( SQUIDGETEST_WIN32_SOURCE_FILES
   )

set( SQUIDGETEST_HEADER_FILES
   )

set( SQUIDGETEST_OSX_HEADER_FILES
   )

set( SQUIDGETEST_WIN32_HEADER_FILES
   )

set( SQUIDGETEST_PUBLIC_HEADER_FILES
   )

#=================================
# Setup SQUIDGETEST preprocessor defines
#=================================
set( SQUIDGETEST_DEFINITIONS
    -DBOOST_ALL_NO_LIB
   )

#=================================
# Setup where to search for header files
#=================================
set( SQUIDGETEST_INCLUDE_DIRECTORIES
   "${SQUIDGE_SOURCE_DIR}"
   "${gtest_SOURCE_DIR}/include"
   "${gtest_SOURCE_DIR}"
   )

set( SQUIDGETEST_INTERNAL_INCLUDE_DIRECTORIES
    ${Boost_INCLUDE_DIRS}
    ${SDL_INCLUDE_DIR}
    ${SDLIMAGE_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    "${SQUIDGE_SOURCE_DIR}/library"
   )

#=================================
# Setup the libraries SQUIDGETEST links to
#=================================
set( SQUIDGETEST_LINK_LIBRARIES
    ${Boost_LIBRARIES}
    ${gtest_LIBRARIES}
   )

#=================================
# Setup Win32 build settings
#=================================
if( WIN32 )
   list( APPEND SQUIDGETEST_SOURCE_FILES
      ${SQUIDGETEST_WIN32_SOURCE_FILES}
      ${SQUIDGETEST_WIN32_HEADER_FILES} )

   # Minimum supported version is Windows XP RTM.
   # http://msdn.microsoft.com/en-us/library/aa383745%28v=vs.85%29.aspx
   add_definitions( -D_WIN32_WINNT=0x0501 )

   set( SQUIDGETEST_EXPORT_RESOURCES_DIR
      ${SQUIDGETEST_BINARY_DIR}/bin/Resources
      )
endif()

#=================================
# Setup OSX build settings
#=================================
if( APPLE )
   find_library( COCOA_FRAMEWORK Cocoa )
   list( APPEND SQUIDGETEST_SOURCE_FILES
      ${SQUIDGETEST_OSX_SOURCE_FILES}
      ${SQUIDGETEST_OSX_HEADER_FILES} )
   list( APPEND SQUIDGETEST_LINK_LIBRARIES ${COCOA_FRAMEWORK} )
endif()

#=================================
# Define the build target for SQUIDGETEST
#=================================
add_definitions( ${SQUIDGETEST_DEFINITIONS} )
include_directories(
   ${SQUIDGETEST_INCLUDE_DIRECTORIES}
   ${SQUIDGETEST_INTERNAL_INCLUDE_DIRECTORIES} )

add_executable(
   SquidgeTests
   ${SQUIDGETEST_SOURCE_FILES}
   ${SQUIDGETEST_HEADER_FILES} )

target_link_libraries(
   SquidgeTests
   gtest
   gtest_main
   ${SQUIDGETEST_LINK_LIBRARIES} )

# Define a target that will run the component test binary
# as part of the build process.
add_custom_target(
   SquidgeTestRunner ALL
   COMMAND ${SQUIDGE_BINARY_DIR}/bin/SquidgeTests
   )
add_dependencies(SquidgeTestRunner SquidgeTests)
