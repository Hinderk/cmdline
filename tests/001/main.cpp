
#include <iostream>
#include <vector>
#include <stdlib.h>

#include "cmdline/optionparser.h"



int main( int argc, const char *argv[] )
{
  OptionParser *Options = CreateOptionParser( argc, argv ) ;

  OptionValue F1( 0.0f ) ;
  OptionValue U1( 10u ) ;
  OptionValue I1( 128 ) ;
  OptionValue B1( false ) ;
  OptionValue S1( "Default" ) ;

  OptionIndex Type[] = {
    Options -> AddOption( F1, "-f", "--float" ) ,
    Options -> AddOption( U1, "-C", "--count" ) ,
    Options -> AddOption( I1, "-i", "--index" ) ,
    Options -> AddOption( B1, "-v", "--verbose" ) ,
    Options -> AddOption( S1, "-N", "--name" )
  } ;

  int state = Options -> Parse() ;
  if ( state )  return state ;

  OptionValue Result ;

  int n = Options -> QueryOption( Result, Type[2] ) ;
  while ( n )
  {
    std::cout << "Option:  " << Result.GetString() << std::endl ;
    n = Options -> NextOption( Result ) ;
  }

  Options -> Discard() ;

  return 0 ;
}
