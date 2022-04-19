
# Explicitly list the source files which make up the library ...

SET( SRCFILES  "optionparser.cpp" 
               "optionvalue.cpp" 
               "cmdline.cpp" 
               "console.cpp"       )

# Create the target for the build system ...

ADD_LIBRARY( ${LIBNAME} ${SRCFILES} )
ADD_LIBRARY( ${LIBNAME}::${LIBNAME} ALIAS ${LIBNAME} )

SET( LIB_VERSION ${SO_VERSION}.${MINOR_VERSION} )

SET_TARGET_PROPERTIES( ${LIBNAME} PROPERTIES VERSION ${LIB_VERSION} )
SET_TARGET_PROPERTIES( ${LIBNAME} PROPERTIES SOVERSION ${SO_VERSION} )

# Generate a header file to facilitate the export of symbols ...

INCLUDE( GenerateExportHeader )

GENERATE_EXPORT_HEADER( 
  ${LIBNAME} 
  EXPORT_FILE_NAME "include/cmdline/cmdexport.h"
)

# Append the letter 'd' if the library contains debug symbols ...

IF( CMDLINE_DEBUG_SYMBOLS )
  STRING( PREPEND CMAKE_STATIC_LIBRARY_SUFFIX "d" )
  STRING( PREPEND CMAKE_SHARED_LIBRARY_SUFFIX "d" )
ENDIF( CMDLINE_DEBUG_SYMBOLS )

# The following compiler switches are used to configure the build 
# process on all Unix systems which use GNU development tools.

#IF( UNIX )
#  ADD_DEFINITIONS( -frtti )
#ENDIF( UNIX )

# The following settings are used to build the library with some
# native C++ compiler on a Windows box (e.g. VS2019):

IF( WIN32 )
  SET( CMAKE_STATIC_LIBRARY_PREFIX "" )
  SET( CMAKE_SHARED_LIBRARY_PREFIX "" )
ENDIF( WIN32 )

# The following settings apply to both Windows and Posix builds ...

TARGET_COMPILE_FEATURES( ${LIBNAME} PUBLIC cxx_std_11 )


TARGET_INCLUDE_DIRECTORIES( 
  ${LIBNAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../interface>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)

TARGET_COMPILE_DEFINITIONS(
  ${LIBNAME}
  PUBLIC 
    $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${LIBNAME}_STATIC_DEFINE>
)
