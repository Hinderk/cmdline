
#include "cmdline/console.h"
#include "cmdline/optionparser.h"


#ifdef _WIN32


int Console::QueryWidth( unsigned &CurrentWidth )
{
  HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE ) ;
  if ( hConsole != INVALID_HANDLE_VALUE )
  {
    CONSOLE_SCREEN_BUFFER_INFO Info ;
    if ( GetConsoleScreenBufferInfo( hConsole, &Info ) )
    {
      CurrentWidth = Info.dwMaximumWindowSize.X ;
      return 0 ;
    }
    return CMD_CONSOLE_QUERY_FAILED ;
  }
  return CMD_NO_CONSOLE_FOUND ;
}

#else      // _WIN32


int Console::QueryWidth( unsigned &CurrentWidth )
{
  winsize W0 ;
  if ( ioctl( STDOUT_FILENO, TIOCGWINSZ, &W0 ) < 0 )
    return CMD_CONSOLE_QUERY_FAILED ;
  CurrentWidth = W0.ws_col ;
  return 0 ;
}


#endif     // _WIN32