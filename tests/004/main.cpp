
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <memory>

#include "optionparser.h"



int main( int argc, const char *argv[] )
{
  try {
    OptionValue OV( "Test successful!" ) ;
    std::shared_ptr<OptionParser> Options( CreateOptionParser(argc,argv) ) ;
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

    const char *Test = OV ;
    std::cout << "String output: " << Test << std::endl ;

  }
  catch ( std::bad_cast &e )
  {
    std::cout << "Exception caught: " << e.what() << std::endl ;
  }
  return 0 ;
}
