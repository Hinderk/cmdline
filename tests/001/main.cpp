
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

  CmdOption Result ;

  int n = Options.QueryOption( Result, Type[2] ) ;
  while ( n )
  {
    std::cout << "Option:  " << (int) Result << std::endl ;
    n = Options.NextOption( Result, Type[2] ) ;
  }

  CmdOption A( 1.0 ) ;
  CmdOption B( 5u ) ;
  CmdOption C( 200l ) ;
  CmdOption L ;
  CmdOption S( "filename" ) ;
  std::vector<CmdOption> list = { A, B, C, L, S } ;
  unsigned U( B ) ;
  if ( U != 5 )  return -10 ;

  std::cout << (int) TypeIndex<int>::value << std::endl ;
  std::cout << (int) TypeIndex<float>::value << std::endl ;
  std::cout << (int) TypeIndex<bool>::value << std::endl ;
  std::cout << (int) TypeIndex<const char*>::value << std::endl ;

  for ( const auto &s : list )
  {
    switch ( s.Type() )
    {
      case OptionType::UNSIGNED:
        std::cout << "Unsigned: " << (unsigned short) s << std::endl ;
        break ;
      case OptionType::INTEGER:
        std::cout << " Integer: " << (int) s << std::endl ;
        break ;
      case OptionType::FLOAT:
        std::cout << "   Float: " << (float) s << std::endl ;
        break ;
      case OptionType::BOOLEAN:
        std::cout << " Boolean: " << (bool) s << std::endl ;
        break ;
      case OptionType::STRING:
        std::cout << "  String: " << s.str() << std::endl ;
        break ;
      default:
        ;
    }
  }

  return 0 ;
}
