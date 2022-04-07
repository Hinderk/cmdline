
CMAKE_MINIMUM_REQUIRED( VERSION 3.2...3.9 )

PROJECT( COMMANDLINE_PARSER VERSION 1.0.0 LANGUAGES CXX )

# Specifiy the name of the library ...

SET( LIBNAME "CmdLine" )

# Enable tight control over those symbols that are going to be
# exported by the shared library.

#IF( NOT DEFINED CMAKE_CXX_VISIBILITY_PRESET AND
#    NOT DEFINED CMAKE_VISIBILITY_INLINES_HIDDEN )
#  SET( CMAKE_CXX_VISIBILITY_PRESET HIDDEN )
#  SET( CMAKE_VISIBILITY_INLINES_HIDDEN YES )
#ENDIF()

SET( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

# Specify version information for the project:

SET( SO_VERSION "1" )
SET( MINOR_VERSION "0.0" )

# Facilitate the generation of a shared library if the variable
# CMDLINE_BUILD_SHARED_LIB has been defined.

IF( DEFINED CMDLINE_BUILD_SHARED_LIB )
  SET( BUILD_SHARED_LIBS "${CMDLINE_BUILD_SHARED_LIB}" )
ENDIF()

# The following switch turns the automated unit tests on or off. To
# disable the compilation of test code simply remove the line below.

ENABLE_TESTING()

# Define the folders containing the source code for the converter.

ADD_SUBDIRECTORY( "src" )
ADD_SUBDIRECTORY( "tests" )

# Provide an installer unless the project is build as part of a 
# larger project which has installation procedures of its own to deal
# with this library if that is necessary at all.

STRING( COMPARE EQUAL 
  "${CMAKE_SOURCE_DIR}" 
  "${CMAKE_CURRENT_SOURCE_DIR}"
  provide_installer
)

OPTION( 
  CMDLINE_INCLUDE_PACKAGING 
  "Provide an installer for the library" 
  "${provide_installer}"
)

IF( CMDLINE_INCLUDE_PACKAGING )
  ADD_SUBDIRECTORY( "install" )
ENDIF( CMDLINE_INCLUDE_PACKAGING )