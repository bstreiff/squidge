#=================================
# List all the source files for SQUIDGE
#=================================
set( SQUIDGE_SOURCE_FILES
    "${SQUIDGE_SOURCE_DIR}/client/Level.cpp"
    "${SQUIDGE_SOURCE_DIR}/client/LevelGenerator.cpp"
    "${SQUIDGE_SOURCE_DIR}/client/ResourceManager.cpp"
    "${SQUIDGE_SOURCE_DIR}/client/SDL/Initializer.cpp"
    "${SQUIDGE_SOURCE_DIR}/client/SDL/Window.cpp"
    "${SQUIDGE_SOURCE_DIR}/client/SpriteBatch.cpp"
    "${SQUIDGE_SOURCE_DIR}/client/Stopwatch.cpp"
    "${SQUIDGE_SOURCE_DIR}/client/Texture.cpp"
    "${SQUIDGE_SOURCE_DIR}/client/main.cpp"
    "${SQUIDGE_SOURCE_DIR}/common/platformUtilities.cpp"
    "${SQUIDGE_SOURCE_DIR}/common/Point.cpp"
    "${SQUIDGE_SOURCE_DIR}/common/Vector2.cpp"
    "${SQUIDGE_SOURCE_DIR}/common/Rectangle.cpp"
   )

set( SQUIDGE_OSX_SOURCE_FILES
   )

set( SQUIDGE_WIN32_SOURCE_FILES
   )

set( SQUIDGE_HEADER_FILES
   )

set( SQUIDGE_OSX_HEADER_FILES
   )

set( SQUIDGE_WIN32_HEADER_FILES
   )

set( SQUIDGE_PUBLIC_HEADER_FILES
   )

set( SQUIDGE_RESOURCES
    "${SQUIDGE_SOURCE_DIR}/resources/brick_wall.png"
    "${SQUIDGE_SOURCE_DIR}/resources/bricks.png"
    "${SQUIDGE_SOURCE_DIR}/resources/dirt.png"
    "${SQUIDGE_SOURCE_DIR}/resources/dirt_wall.png"
   )

#=================================
# Setup SQUIDGE preprocessor defines
#=================================
set( SQUIDGE_DEFINITIONS
    -DBOOST_ALL_NO_LIB
   )

#=================================
# Setup where to search for header files
#=================================
set( SQUIDGE_INCLUDE_DIRECTORIES
   "${SQUIDGE_SOURCE_DIR}"
   )

set( SQUIDGE_INTERNAL_INCLUDE_DIRECTORIES
    ${Boost_INCLUDE_DIRS}
    ${SDL_INCLUDE_DIR}
    ${SDLIMAGE_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${Eigen_INCLUDE_DIR}
   )

#=================================
# Setup the libraries SQUIDGE links to
#=================================
set( SQUIDGE_LINK_LIBRARIES
    ${Boost_LIBRARIES}
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${OPENGL_LIBRARIES}
    SDLmain
   )

#=================================
# Setup Win32 build settings
#=================================
if( WIN32 )
   list( APPEND SQUIDGE_SOURCE_FILES
      ${SQUIDGE_WIN32_SOURCE_FILES}
      ${SQUIDGE_WIN32_HEADER_FILES} )

   # Minimum supported version is Windows XP RTM.
   # http://msdn.microsoft.com/en-us/library/aa383745%28v=vs.85%29.aspx
   add_definitions( -D_WIN32_WINNT=0x0501 )

   set( SQUIDGE_EXPORT_RESOURCES_DIR
      ${SQUIDGE_BINARY_DIR}/bin/Resources
      )
endif()

#=================================
# Setup OSX build settings
#=================================
if( APPLE )
   find_library( COCOA_FRAMEWORK Cocoa )
   list( APPEND SQUIDGE_SOURCE_FILES
      ${SQUIDGE_OSX_SOURCE_FILES}
      ${SQUIDGE_OSX_HEADER_FILES} )
   list( APPEND SQUIDGE_LINK_LIBRARIES ${COCOA_FRAMEWORK} )
   set( SQUIDGE_EXPORT_RESOURCES_DIR
      ${SQUIDGE_BINARY_DIR}/bin/Squidge.app/Contents/Resources
      )
endif()

#=================================
# Define the build target for SQUIDGE
#=================================
add_definitions( ${SQUIDGE_DEFINITIONS} )
include_directories(
   ${SQUIDGE_INCLUDE_DIRECTORIES}
   ${SQUIDGE_INTERNAL_INCLUDE_DIRECTORIES} )

add_executable(
   Squidge
   WIN32
   MACOSX_BUNDLE
   ${SQUIDGE_SOURCE_FILES}
   ${SQUIDGE_HEADER_FILES} )

target_link_libraries(
   Squidge
   ${SQUIDGE_LINK_LIBRARIES} )

add_custom_target(
   SquidgeResources ALL
   COMMAND ${CMAKE_COMMAND} -E copy_directory ${SQUIDGE_SOURCE_DIR}/resources ${SQUIDGE_EXPORT_RESOURCES_DIR}
   SOURCES ${SQUIDGE_RESOURCES}
   )

#=================================
# Export build settings needed by samples
#=================================
set( SQUIDGE_DEFINITIONS ${SQUIDGE_DEFINITIONS} PARENT_SCOPE )
set( SQUIDGE_INCLUDE_DIRECTORIES ${SQUIDGE_INCLUDE_DIRECTORIES} PARENT_SCOPE )

#=================================
# Doxygen target
#=================================
find_package( Doxygen )

if( DOXYGEN_FOUND )
   message( STATUS "Doxygen found.  Build the doc target/project to generate API documentation." )

   set( DOXYGEN_SOURCE_DIRS
       "${SQUIDGE_SOURCE_DIR}/include"
       "${SQUIDGE_SOURCE_DIR}/library" )
   string( REGEX REPLACE ";" " " DOXYGEN_INPUT "${DOXYGEN_SOURCE_DIRS}" )

   set( DOXYGEN_OUTPUT_DIR
       "${SQUIDGE_SOURCE_DIR}/docs" )

   set( DOXYGEN_FILE_PATTERNS "*.h" )

   configure_file( "${SQUIDGE_SOURCE_DIR}/Doxyfile.in"
               "${SQUIDGE_BINARY_DIR}/Doxyfile" )
   add_custom_target( doc
                  "${DOXYGEN_EXECUTABLE}" "${SQUIDGE_BINARY_DIR}/Doxyfile"
                  DEPENDS "${SQUIDGE_BINARY_DIR}/Doxyfile" )
else()
   message( STATUS "Doxygen NOT found.  The doc target/project will NOT be created." )
endif()
