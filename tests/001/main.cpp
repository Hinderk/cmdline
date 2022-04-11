
#include <iostream>
#include <vector>
#include <stdlib.h>

#include "optionparser.h"
#include "optionvalue.h"



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

//  CmdOption A( 1.0 ) ;
//  CmdOption B( 5u ) ;
//  CmdOption C( 200l ) ;
//  CmdOption L ;
//  CmdOption S( "filename" ) ;
//  std::vector<CmdOption> list = { A, B, C, L } ;
//  unsigned U( B ) ;
//  if ( U != 5 )  return -10 ;

/*
  for ( const auto &s : list )
  {
    switch ( s.Type() )
    {
      case CMD_UINT32_T:
        std::cout << "Unsigned: " << (unsigned) s << std::endl ;
        break ;
      case CMD_INT32_T:
        std::cout << " Integer: " << (int) s << std::endl ;
        break ;
      case CMD_FLOAT32_T:
        std::cout << "   Float: " << (float) s << std::endl ;
        break ;
      case CMD_BOOL_T:
        std::cout << " Boolean: " << (bool) s << std::endl ;
        break ;
      case CMD_STRING_T:
        std::cout << "  String: " << (const char *) s << std::endl ;
        break ;
      default:
        ;
    }
  }
*/

  return 0 ;
}
