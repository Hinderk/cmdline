
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <memory>

extern FILE *Log ;

#define __CMD_MAIN

#include "cmdline/optionparser.h"




struct Error {

  int n ;
  int m ;

} ;



std::ostream& operator<<( std::ostream &Out, const Error &e )
{
  Out << e.n << " -- " << e.m ;
  return Out ;
}



int main( int argc, const char *argv[] )
{
  std::shared_ptr<OptionParser> Options( CreateOptionParser(argc,argv) ) ;
  Error e { 1, 2 } ;
  try {
    OptionValue T0 ;
    OptionValue E0( e ) ;
    OptionValue F1( 18.4f ) ;
    OptionValue U1( 10u ) ;
    OptionValue I1( 128 ) ;
    OptionValue B1( false ) ;
    OptionValue S1( "Success!" ) ;

    OptionIndex Type[] = {
      Options -> AddOption( F1, "-f", "--float" ) ,
      Options -> AddOption( U1, "-C", "--count" ) ,
      Options -> AddOption( I1, "-i", "--index" ) ,
      Options -> AddOption( B1, "-v", "--verbose" ) ,
      Options -> AddOption( S1, "-N", "--name" ) ,
      Options -> AddOption( E0, "-e", "--error" ) , 0
    } ;

    int state = Options -> Parse() ;
    if ( state )  return state ;

    const char *Test = S1 ;
    std::cout << "String output: " << Test << std::endl ;
    T0 = "Success again!" ;

    OptionValue Result ;

    for ( OptionIndex i : Type )
    {
      std::cout << "Current type: " << i << "\n" ;
      int n = Options -> QueryOption( Result, i ) ;
      while ( n )
      {
        std::cout << "Option:  " << Result.GetString() << std::endl ;
        n = Options -> NextOption( Result ) ;
      }
    }

  }
  catch ( std::bad_cast &e )
  {
    std::cout << "Exception caught: " << e.what() << std::endl ;
  }
  return 0 ;
}
