
#include <iostream>
#include <vector>
#include <stdlib.h>

#include "optionparser.h"



int main( int argc, const char *argv[] )
{
  OptionValue OV( NULL ) ;
  OptionParser *Options = CreateOptionParser( argc, argv ) ;
  int state ;
  OptionIndex Type[] = {
    Options -> AddOption( 0.0f, "-f", "--float" ) ,
    Options -> AddOption( 0u, "-u", "--unsigned" ) ,
    Options -> AddOption( 0, "-i", "--integer" ) ,
    Options -> AddOption( true, "-b", "--bool" ) ,
    Options -> AddOption( "", "-s", "--string" ) ,
    Options -> AddOption( OV, "-e", "--empty" )
  } ;

  state = Options -> Parse() ;
  if ( state )  return state ;


  Options -> Discard() ;

  return 0 ;
}
