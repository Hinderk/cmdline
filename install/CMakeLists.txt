
INCLUDE( GNUInstallDirs )
INCLUDE( CMakePackageConfigHelpers )

# As various package management systems have different standards where to put CMake 
# package configuration scripts a cache variable is created to allow for user input. 

IF ( NOT DEFINED CMDLINE_INSTALL_CMAKEDIR )
  SET( 
    CMDLINE_INSTALL_CMAKEDIR
    "${CMAKE_INSTALL_LIBDIR}/cmake/${LIBNAME}"
    CACHE STRING 
    "Path to the ${LIBNAME} CMake files"
)
ENDIF()

INSTALL( TARGETS ${LIBNAME} EXPORT ${LIBNAME}_Targets
         RUNTIME  COMPONENT ${LIBNAME}_Runtime
         LIBRARY  COMPONENT ${LIBNAME}_Runtime
         NAMELINK_COMPONENT ${LIBNAME}_Development
         ARCHIVE  COMPONENT ${LIBNAME}_Development
         INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}" )

INSTALL( 
  DIRECTORY 
    "${CMAKE_SOURCE_DIR}/include/" 
    "${CMAKE_BINARY_DIR}/src/include/"
  TYPE INCLUDE
  COMPONENT ${LIBNAME}_Development
)

IF( BUILD_SHARED_LIBS )
  SET( type "shared" )
ELSE( BUILD_SHARED_LIBS )
  SET( type "static" )
ENDIF( BUILD_SHARED_LIBS )

INSTALL(
  EXPORT ${LIBNAME}_Targets
  DESTINATION "${CMDLINE_INSTALL_CMAKEDIR}"
  NAMESPACE ${LIBNAME}::
  FILE ${LIBNAME}-${type}-targets.cmake
  COMPONENT ${LIBNAME}_Development
)

# Create a file containing version information ... 

WRITE_BASIC_PACKAGE_VERSION_FILE(
  "${LIBNAME}ConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion
)

INSTALL(
  FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/${LIBNAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${LIBNAME}ConfigVersion.cmake"
  DESTINATION "${CMDLINE_INSTALL_CMAKEDIR}"
  COMPONENT ${LIBNAME}_Development
)
