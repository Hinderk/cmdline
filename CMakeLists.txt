
CMAKE_MINIMUM_REQUIRED( VERSION 3.15 )

PROJECT( "CmdLine" VERSION 1.0.0 LANGUAGES CXX )

# Specifiy the name of the library. Certain generated header files
# interact with the source code of the library & will surely break
# the code if this string is changed.

SET( LIBNAME "CmdLine" )

# Enable tight control over those symbols that are going to be
# exported by the shared library.

IF( NOT DEFINED CMAKE_CXX_VISIBILITY_PRESET AND
    NOT DEFINED CMAKE_VISIBILITY_INLINES_HIDDEN )
  SET( CMAKE_CXX_VISIBILITY_PRESET "hidden" )
  SET( CMAKE_VISIBILITY_INLINES_HIDDEN YES )
ENDIF()

# Specify version information for the project:

SET( SO_VERSION "1" )
SET( MINOR_VERSION "0.0" )

# Detect if the project is built by itself of as one part of some
# larger project. In the former case a number of options may be
# used to modify the build procedure ...

STRING( COMPARE EQUAL
  "${CMAKE_SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}"
  PROVIDE_OPTIONS
)

# Detect the presence of debug symbols in the compiler artifacts
# as this may affect the packaging of the library ...

##SET( CMDLINE_RELEASE_BUILD ON )
IF( DEFINED CMAKE_BUILD_TYPE AND CMAKE_BUILD_TYPE )
  STRING( TOUPPER "${CMAKE_BUILD_TYPE}" NORMALISED_BUILD_TYPE )
  IF( ${NORMALISED_BUILD_TYPE} MATCHES "DEBUG" OR
      ${NORMALISED_BUILD_TYPE} MATCHES "RELWITHDEBINFO" )
  ##  SET( CMDLINE_RELEASE_BUILD OFF )
    OPTION( CMDLINE_SEPARATE_DEBUG_SYMBOLS
            "Create a separate package with debug symbols."
            OFF
    )
    IF( CMDLINE_SEPARATE_DEBUG_SYMBOLS )
      SET( CMDLINE_DEBUG_SYMBOLS OFF )
    ENDIF()
  ENDIF()
ENDIF()

# Facilitate the generation of a shared library if the variable
# CMDLINE_BUILD_SHARED_LIB has been defined.

IF ( PROVIDE_OPTIONS )
  OPTION(
    CMDLINE_BUILD_SHARED_LIB
    "Create a shared library (dll)."
    YES
  )
ENDIF( PROVIDE_OPTIONS )

# Trigger the build of a shared library by setting the appropriate
# internal CMake variable  ... (BUILD_SHARED_LIBS)

IF( DEFINED CMDLINE_BUILD_SHARED_LIB )
  SET( BUILD_SHARED_LIBS "${CMDLINE_BUILD_SHARED_LIB}" )
  SET( CMDLINE_MONOLITHIC_BUILD OFF )
ELSE()
  OPTION(
    CMDLINE_MONOLITHIC_BUILD
    "Create a monolithic build."
    NO
  )
ENDIF()

# The following switch turns the automated unit tests on or off. To
# disable the compilation of test code simply remove the line below.

ENABLE_TESTING()

# Define the folders containing the source code for the converter.

ADD_SUBDIRECTORY( "src" )
ADD_SUBDIRECTORY( "tests" )

# Provide an installer unless the project is built as some part of a
# larger project which has installation procedures of its own to deal
# with this library - should that prove necessary at all.

OPTION(
  CMDLINE_INCLUDE_PACKAGING
  "Provide an installer for the library"
  "${PROVIDE_OPTIONS}"
)

IF( CMDLINE_INCLUDE_PACKAGING )
  ADD_SUBDIRECTORY( "install" )
ENDIF( CMDLINE_INCLUDE_PACKAGING )
