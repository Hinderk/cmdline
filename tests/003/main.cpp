
#include <iostream>
#include <vector>
#include <stdlib.h>

#include "cmdline/optionparser.h"



int main( int argc, const char *argv[] )
{
  OptionParser *Options = CreateOptionParser( argc, argv ) ;
  int state ;
  OptionIndex Type[] = {
    Options -> AddOption( 55.5f, "-f", "--float" ) ,
    Options -> AddOption( 10u, "-C", "--count" ) ,
    Options -> AddOption( -120, "-i", "--index" ) ,
    Options -> AddOption( false, "-v", "--verbose" ) ,
    Options -> AddOption( "The Message!", "-N", "--name" )
  } ;

  Options -> UseDefault( Type[0], true, "m/s" ) ;
  Options -> UseDefault( Type[1], true, "hours" ) ;
  Options -> UseDefault( Type[2], true, NULL ) ;
  Options -> UseDefault( Type[4], true, NULL ) ;

  Options -> AddName( Type[0], "Rate" ) ;

  Options -> AddOption( CMD_STRING_T, 1, "File" ) ;
  Options -> AddOption( CMD_FLOAT64_T, 5, NULL ) ;
  Options -> AddOption( CMD_UINT64_T, 7, "Test" ) ;

  state = Options -> EnforceOption( Type[3] ) ;   // Boolean options are
  if ( state == 0 )  return -2 ;                  // not enforcable ...


  Options -> EnforceOption( 9 ) ;
//  Options -> EnforceOption( 6, false ) ;

  state = Options -> Parse() ;
  if ( state )  return state ;

  char Message[ 1024 ] ;
  Options -> Usage( Message, 1024 ) ;
  std::cout << Message << "\n" ;

//   DestroyOptionParser( Options )  ;


  Options -> Discard() ;

  return 0 ;
}
