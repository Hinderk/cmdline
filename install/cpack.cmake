
# General settings applicable to all CPack generators follow:

SET( CPACK_PACKAGE_VERSION_MINOR "0" )
IF( CMDLINE_RELEASE_BUILD )
  SET( CPACK_PACKAGE_VERSION_MAJOR "release-1" )
ELSE()
  SET( CPACK_PACKAGE_VERSION_MAJOR "debug-1" )
ENDIF()

IF( CMDLINE_DEBUG_SYMBOLS )
  SET( CPACK_STRIP_FILES OFF )
ELSE()
  SET( CPACK_STRIP_FILES ON )
ENDIF()

SET( CPACK_PACKAGE_DESCRIPTION_SUMMARY
     "A simple, portable command line parser written in C++11." )

SET( CPACK_PACKAGE_VENDOR "Hinderk Buss" )
SET( CPACK_PACKAGE_CONTACT "Hinderk Buss" )

SET( CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/INFO.md" )
SET( CPACK_PACKAGE_LICENSE_FILE "${CMAKE_SOURCE_DIR}/LICENSE" )

SET( CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md" )
SET( CPACK_RESOURCE_FILE_WELCOME "${CMAKE_CURRENT_SOURCE_DIR}/ABOUT.md" )
SET( CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE" )

SET( CPACK_PACKAGE_DIRECTORY "${CMAKE_BINARY_DIR}/cpack" )

SET( CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/Hinderk/cmdline" )

SET( CPACK_PACKAGE_CHECKSUM "SHA256" )
SET( CPACK_VERBATIM_VARIABLES ON )
SET( CPACK_MONOLITHIC_INSTALL OFF )

#############################################################################

# CPACK_PACKAGE_VERSION_PATCH
# CPACK_PACKAGE_ICON
# CPACK_PACKAGE_FILE_NAME       ## The default is used based on package names. 
#
# CPACK_PROJECT_CONFIG_FILE
# CPACK_PACKAGE_DESCRIPTION     ## Taken from the description file ...
# CPACK_OUTPUT_CONFIG_FILE

# CPACK_PACKAGE_EXECUTABLES     ## None are present in this package ...
# CPACK_THREADS
