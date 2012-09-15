#=================================
# List all the source files for SquidgeCommon
#=================================
set( SQUIDGECOMMON_SOURCE_FILES
    "${SQUIDGE_SOURCE_DIR}/common/platformUtilities.cpp"
    "${SQUIDGE_SOURCE_DIR}/common/Matrix.cpp"
    "${SQUIDGE_SOURCE_DIR}/common/Point.cpp"
    "${SQUIDGE_SOURCE_DIR}/common/Vector2.cpp"
    "${SQUIDGE_SOURCE_DIR}/common/Vector3.cpp"
    "${SQUIDGE_SOURCE_DIR}/common/Vector4.cpp"
    "${SQUIDGE_SOURCE_DIR}/common/Rectangle.cpp"
   )

set( SQUIDGECOMMON_OSX_SOURCE_FILES
   )

set( SQUIDGECOMMON_WIN32_SOURCE_FILES
   )

set( SQUIDGECOMMON_HEADER_FILES
   )

set( SQUIDGECOMMON_OSX_HEADER_FILES
   )

set( SQUIDGECOMMON_WIN32_HEADER_FILES
   )

#=================================
# Setup SQUIDGE preprocessor defines
#=================================
set( SQUIDGECOMMON_DEFINITIONS
    -DBOOST_ALL_NO_LIB
   )

#=================================
# Setup where to search for header files
#=================================
set( SQUIDGECOMMON_INCLUDE_DIRECTORIES
   "${SQUIDGE_SOURCE_DIR}"
   )

set( SQUIDGECOMMON_INTERNAL_INCLUDE_DIRECTORIES
    ${Boost_INCLUDE_DIRS}
   )

#=================================
# Setup the libraries SQUIDGE links to
#=================================
set( SQUIDGECOMMON_LINK_LIBRARIES
    ${Boost_LIBRARIES}
   )

#=================================
# Setup Win32 build settings
#=================================
if( WIN32 )
   list( APPEND SQUIDGECOMMON_SOURCE_FILES
      ${SQUIDGECOMMON_WIN32_SOURCE_FILES}
      ${SQUIDGECOMMON_WIN32_HEADER_FILES} )

   # Minimum supported version is Windows XP RTM.
   # http://msdn.microsoft.com/en-us/library/aa383745%28v=vs.85%29.aspx
   add_definitions( -D_WIN32_WINNT=0x0501 )
endif()

#=================================
# Setup OSX build settings
#=================================
if( APPLE )
   find_library( COCOA_FRAMEWORK Cocoa )
   list( APPEND SQUIDGECOMMON_SOURCE_FILES
      ${SQUIDGECOMMON_OSX_SOURCE_FILES}
      ${SQUIDGECOMMON_OSX_HEADER_FILES} )
   list( APPEND SQUIDGE_LINK_LIBRARIES ${COCOA_FRAMEWORK} )
endif()

#=================================
# Define the build target for SQUIDGE
#=================================
add_definitions( ${SQUIDGECOMMON_DEFINITIONS} )
include_directories(
   ${SQUIDGECOMMON_INCLUDE_DIRECTORIES}
   ${SQUIDGECOMMON_INTERNAL_INCLUDE_DIRECTORIES} )

add_library(
   SquidgeCommon
   STATIC
   ${SQUIDGECOMMON_SOURCE_FILES}
   ${SQUIDGECOMMON_HEADER_FILES} )

#=================================
# Export build settings needed by samples
#=================================
set( SQUIDGECOMMON_DEFINITIONS ${SQUIDGE_DEFINITIONS} PARENT_SCOPE )
set( SQUIDGECOMMON_INCLUDE_DIRECTORIES ${SQUIDGE_INCLUDE_DIRECTORIES} PARENT_SCOPE )
