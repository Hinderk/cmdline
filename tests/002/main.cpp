
#include <iostream>
#include <vector>
#include <stdlib.h>

#include "cmdline.h"



int main( int argc, const char *argv[] )
{
  CmdLine Options( argc, argv ) ;
  OptionIndex Type[] = {
    Options.AddOption( 55.5f, "-f", "--float" ) ,
    Options.AddOption( 10u, "-C", "--count" ) ,
    Options.AddOption( -120, "-i", "--index" ) ,
    Options.AddOption( false, "-v", "--verbose" ) ,
    Options.AddOption( "The Message!", "-N", "--name" )
  } ;
  int state = Options.Parse() ;
  if ( state )  return state ;

  Options.UseDefault( Type[0], true, "m/s" ) ;
  Options.UseDefault( Type[1], true, "hours" ) ;
  Options.UseDefault( Type[2], true, NULL ) ;
  Options.UseDefault( Type[4], true, NULL ) ;

  state = Options.UseDefault( Type[3], true, NULL ) ;   // No defaults here!
  if ( state == 0 )  return -1 ;                        // Expect error ...

  Options.AddName( Type[0], "Rate" ) ;

  Options.AddOption( CMD_STRING_T, 1, "File" ) ;
  Options.AddOption( CMD_STRING_T, 5, "Output" ) ;
  Options.AddOption( CMD_FLOAT32_T, 7, "Test" ) ;

  state = Options.EnforceOption( Type[3], true ) ;
  if ( state == 0 )  return -2 ;


  Options.EnforceOption( 9, true ) ;
//  Options.EnforceOption( 6, false ) ;

  char Message[ 1024 ] ;
  Options.Usage( Message, 1024 ) ;
  std::cout << Message << "\n" ;

  return 0 ;
}
