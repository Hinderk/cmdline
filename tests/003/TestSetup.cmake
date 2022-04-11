
###############################################################################
#
#   Test the abstract interface of the command line parser ...
#
###############################################################################
#
# This file is used to configure the test driver, which is going to be added 
# to the list of tests one directory level above this one. Note, that this 
# module is simply included in the "CMakeLists.txt" file which resides in the
# subdirectory "tests" of the source tree.
#
###############################################################################

# This string below is used to identify the test. 

SET( TEST_NAME "Dynamic" )

# The name of the binary to be invoked by the "CTest" subsystem. Note
# that in some cases the test driver may be some script, which resides
# in the source tree. In such a situation further CMake directives 
# may be included in this file to setup the test environment...

SET( TEST_BIN "driver-003" )

# The following list, contained in the variable TEST_ARGS, may be used to 
# define arguments which will be passed on to the test driver specified by
# TEST_BIN. Note, that an empty list of test arguments will cause the 
# build system to skip tests in the current source directory. Hence, use 
# whitespace enclosed in quotes to indicate the lack of arguments. Each
# test carries a name, which preceeds the parameter list. To perform a
# number of tests with varying command line switches, use the following
# syntax: <Name 1> "<Switch 11> ...<Switch 1n>" <Name 2> "<Switch 21> ...
# <Switch 2n>" <Name 3> "  " <Name 4> "<Switch 41> ...<Switch 4n>"

SET( TEST_ARGS 01 "-v -f1.0 --float=-123.6e-8"
               02 "--float 2.4e10 -f.005 -C 10"
               03 "--count =3 --count= 9 --count = 12"
               04 "--verbose string_a string_b string_c"
               05 "--name = \"===\" -N filename" )
