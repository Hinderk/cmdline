# Configuration for the Windows Packaging System (NSIS):

SET( CPACK_GENERATOR "NSIS" )

# Force the installer to forego admin privileges. The variable is
# CPACK_NSIS_BRANDING_TEXT_CODE is abused due to its vicinity to
# the code which defines the execution level. The other possible
# solution, changing the CPACK_NSIS_DEFINES variable doesn't work
# as this variable seems to be ignored by cpack. 

SET( CPACK_NSIS_BRANDING_TEXT_CODE "  RequestExecutionLevel user" )
SET( CPACK_NSIS_DEFINES "  RequestExecutionLevel user" )

SET( CPACK_NSIS_INSTALL_ROOT "C:\\Software" )

SET( CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON )
SET( CPACK_NSIS_MODIFY_PATH ON )
SET( CPACK_NSIS_DISPLAY_NAME "CmdLine Library" )
SET( CPACK_NSIS_PACKAGE_NAME "CmdLine Library" )

SET( CPACK_PACKAGE_INSTALL_DIRECTORY "cmdline" )


SET( CPACK_NSIS_URL_INFO_ABOUT "https://github.com/Hinderk/cmdline" )


SET( CPACK_NSIS_MUI_ICON
     "${CMAKE_CURRENT_SOURCE_DIR}/icons/install.ico" )
SET( CPACK_NSIS_MUI_UNIICON 
     "${CMAKE_CURRENT_SOURCE_DIR}/icons/remove.ico" )

SET( CPACK_NSIS_MENU_LINKS 
     "https:\/\/github.com\/Hinderk\/cmdline" "Source Code on GitHub" )

SET( CPACK_NSIS_WELCOME_TITLE 
     "CmdLine - A simple, portable command line parser written in C++" )
SET( CPACK_NSIS_FINISH_TITLE "CmdLine has been installed ..." )
   
SET( CPACK_NSIS_MANIFEST_DPI_AWARE ON )
SET( CPACK_NSIS_BRANDING_TEXT " " )
SET( CPACK_NSIS_BRANDING_TEXT_TRIM_POSITION "CENTER" )


#############################################################################

## CPACK_NSIS_INSTALLED_ICON_NAME
## CPACK_NSIS_EXTRA_PREINSTALL_COMMANDS
## CPACK_NSIS_EXTRA_INSTALL_COMMANDS
## CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS
## CPACK_NSIS_COMPRESSOR
## CPACK_NSIS_UNINSTALL_NAME
## CPACK_NSIS_WELCOME_TITLE_3LINES
## CPACK_NSIS_FINISH_TITLE_3LINES
## CPACK_NSIS_MUI_HEADERIMAGE
## CPACK_NSIS_EXECUTABLE
## CPACK_NSIS_IGNORE_LICENSE_PAGE
## CPACK_NSIS_EXECUTABLE_PRE_ARGUMENTS
## CPACK_NSIS_EXECUTABLE_POST_ARGUMENTS
## CPACK_NSIS_CONTACT
## CPACK_NSIS_<compName>_INSTALL_DIRECTORY
## CPACK_NSIS_CREATE_ICONS_EXTRA
## CPACK_NSIS_DELETE_ICONS_EXTRA
## CPACK_NSIS_EXECUTABLES_DIRECTORY
## CPACK_NSIS_MUI_FINISHPAGE_RUN
