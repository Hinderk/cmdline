
###############################################################################
#
# Define the source files which must be compiled into the test driver...
#
  SET( SOURCES "main.cpp" )
#
###############################################################################
#
# The directories below contain additional header files which be necessary
# to build the unit test. However, relying on other projects is discouraged,
# as each unit test should be as self-contained as possible.
#
##  INCLUDE_DIRECTORIES( $ENV{HOME}/include  )
#
###############################################################################
#
# The following code is completely generic and may be recycled for all unit
# test in the project. The test setup is performed in the module "TestSetup"
# which is supposed to reside in the current directory. The CMake module will
# define the following variables: TEST_NAME, TEST_BIN and TEST_ARGS.
#
  IF( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/TestSetup.cmake )
    INCLUDE( ${CMAKE_CURRENT_SOURCE_DIR}/TestSetup.cmake )
    IF( TEST_ARGS )
      FOREACH( ARGS ${TEST_ARGS} )
        IF( HOLD_NAME )
          SET( HOLD_ARGS ${ARGS} )
          SEPARATE_ARGUMENTS( HOLD_ARGS )
          ADD_TEST( ${TEST_NAME}-${HOLD_NAME} ${TEST_BIN} ${HOLD_ARGS} )
          SET( HOLD_NAME )
        ELSE( HOLD_NAME )
          SET( HOLD_NAME ${ARGS} )
        ENDIF( HOLD_NAME )
      ENDFOREACH( ARGS )
    ELSE( TEST_ARGS )
      ADD_TEST( ${TEST_NAME} ${TEST_BIN} )
    ENDIF( TEST_ARGS )
    ADD_EXECUTABLE( ${TEST_BIN} ${SOURCES} )
#
  ELSE( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/TestSetup.cmake )
#
# In case no dedicated setup script has been supplied for the unit test, a
# generic name for the test is derived from the current source path and the
# test is registered under this designation with the CTest system...
#
    MESSAGE(  "---> No setup script found ..." )
    IF( DEFINED SOURCES )
      SET( TEST_BIN "driver-003" )
      ADD_EXECUTABLE( ${TEST_BIN} ${SOURCES} )
    ENDIF( DEFINED SOURCES )
#
  ENDIF( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/TestSetup.cmake )
#
# To reduce the likelyhood of compatibility issues related to the C runtime
# of older installations of the Windows operating system the test driver is
# built (/MT) and linked statically against the runtime system.
#
  TARGET_LINK_LIBRARIES( ${TEST_BIN} ${LIBNAME} )
#
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
# TARGET_LINK_LIBRARIES( ${TEST_BIN} UnitTest++ )
# TARGET_LINK_LIBRARIES( ${TEST_BIN} efwrap )
# TARGET_LINK_LIBRARIES( ${TEST_BIN} efence )
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
