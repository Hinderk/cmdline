
#include <iostream>
#include <vector>
#include <stdlib.h>

#include "cmdline.h"



int main( int argc, const char *argv[] )
{
  CmdLine Options( argc, argv ) ;
  CmdLine::Option Type[] = {
    Options.AddOption( OptionType::FLOAT, "-f", "--float" ) ,
    Options.AddOption( OptionType::UNSIGNED, "-C", "--count" ) ,
    Options.AddOption( OptionType::INTEGER, "-i", "--index" ) ,
    Options.AddOption( OptionType::BOOLEAN, "-v", "--verbose" ) ,
    Options.AddOption( OptionType::STRING, "-N", "--name" )
  } ;
  int state = Options.Parse() ;
  if ( state )  return state ;

  Options.AddDefault( Type[0], 55.5, "m/s" ) ;
  Options.AddDefault( Type[1], 10u, "hours" ) ;
  Options.AddDefault( Type[2], -120 ) ;
  Options.AddDefault( Type[4], "The Message!" ) ;

  state = Options.AddDefault( Type[3], true ) ;   // No defaults for boolean
  if ( state == 0 )  return -1 ;                  // options. Expect error!

  Options.AddName( Type[0], "Rate" ) ;

  Options.AddName( 1, "File" ) ;
  Options.AddName( 5, "Output" ) ;
  Options.AddName( 7, "Test" ) ;

  state = Options.EnforceOption( Type[3] ) ;
  if ( state == 0 )  return -2 ;


  Options.EnforceOption( 9 ) ;
//  Options.EnforceOption( 6, false ) ;


  std::cout << Options.Usage() << "\n" ;

  return 0 ;
}
