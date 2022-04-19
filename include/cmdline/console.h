
#ifndef __CMD_CONSOLE_H
#define __CMD_CONSOLE_H

#ifdef _WIN32
  #include <Windows.h>
#else
  #include <stdio.h>
  #include <sys/ioctl.h>
#endif




class Console {

  public:

    Console( void ) = default ;

    int QueryWidth( unsigned &Width ) ;

// private:

} ;

#endif     // __CMD_CONSOLE_H
