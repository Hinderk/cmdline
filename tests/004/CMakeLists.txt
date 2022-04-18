
PROJECT( CMDLINE_INSTALLER_TEST )

STRING( COMPARE EQUAL
  "${CMAKE_SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}"
  CMDLINE_TEST_CMAKE_INSTALLER
)

IF( CMDLINE_TEST_CMAKE_INSTALLER )
  CMAKE_MINIMUM_REQUIRED( VERSION 3.12 )
  FIND_PACKAGE( CmdLine 1 COMPONENTS shared )
#  FIND_PACKAGE( CmdLine 1 REQUIRED shared )
  IF( CmdLine_FOUND )
    SET( SOURCES "main.cpp" )
    SET( TESTBIN "driver-004" )
    ADD_EXECUTABLE( ${TESTBIN} ${SOURCES} )
    INCLUDE_DIRECTORIES( "${CMAKE_CURRENT_SOURCE_DIR}/../../include" )
    TARGET_LINK_LIBRARIES( ${TESTBIN} PRIVATE CmdLine::CmdLine )

###############################################################################
#
# If profiling information is required, the ENABLE_CODE_PROFILING variable
# must be defined. The profiling data can be obtained from the executable
# with the help of a tool called "gprof". Currently, this feature is not
# supported under the Windows operating system.
#
    IF( UNIX AND ENABLE_CODE_PROFILING )
      SET_TARGET_PROPERTIES( ${TEST_BIN} PROPERTIES LINK_FLAGS -pg )
    ENDIF( UNIX AND ENABLE_CODE_PROFILING )
#
# Remove the comment in front of the following line if the unit test relies on
# the unit testing framework "UnitTest++":
#
#   TARGET_LINK_LIBRARIES( ${TEST_BIN} UnitTest++ )
#   TARGET_LINK_LIBRARIES( ${TEST_BIN} efwrap )
#   TARGET_LINK_LIBRARIES( ${TEST_BIN} efence )
#
# If information about test coverage is requested, the ENABLE_TEST_COVERAGE
# variable must be defined. The coverage data is generated on Unix systems
# with the help of the "gcov" tool. Currently, test coverage reports are not
# supported under the Windows operating system.
#
    IF( UNIX AND ENABLE_TEST_COVERAGE )
      TARGET_LINK_LIBRARIES( ${TEST_BIN} gcov )
    ENDIF( UNIX AND ENABLE_TEST_COVERAGE )
#
###############################################################################

  ENDIF( CmdLine_FOUND )
ENDIF( CMDLINE_TEST_CMAKE_INSTALLER )
