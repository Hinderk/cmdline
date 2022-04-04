
CMAKE_MINIMUM_REQUIRED( VERSION 2.8.11...3.6 )

PROJECT( COMMANDLINE_PARSER LANGUAGES CXX )

# Specifiy the name of the library ...

SET( LIBNAME "cmdline" )

# Specify version information for the project:

SET( SO_VERSION "1" )
SET( MINOR_VERSION "0.0" )

# Specify the location of header files used by the project.

INCLUDE_DIRECTORIES( "${CMAKE_CURRENT_SOURCE_DIR}/include" )

# The following compiler switches are used to configure the build 
# process on all Unix systems which use GNU development tools.

IF( UNIX )
  ADD_DEFINITIONS( -std=c++11 -frtti )
ENDIF( UNIX )

# The following switch turns the automated unit tests on or off. To
# disable the compilation of test code simply remove the line below.

ENABLE_TESTING()

# Define the folders containing the source code for the converter.

ADD_SUBDIRECTORY( "src" )
ADD_SUBDIRECTORY( "tests" )
