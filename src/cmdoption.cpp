
#include "cmdoption.h"



CmdOption::CmdOption( void ) :

  type( OptionType::BOOLEAN ) ,
  value() ,
  opt( {} ) {}



CmdOption::CmdOption( const char *name ) :

  type( OptionType::STRING ) ,
  value() ,
  opt( {} )
{
  if ( name )  value = name ;
}



CmdOption::CmdOption( const std::string &name ) :

  type( OptionType::STRING ) ,
  value( name ) ,
  opt( {} ) {}



const char* CmdOption::str( void ) const
{
  static char Buffer[ 64 ] ;
  switch ( type )
  {
    case OptionType::INTEGER:
      snprintf( Buffer, 64, "%lli", opt.index ) ;
      break ;
    case OptionType::UNSIGNED:
      snprintf( Buffer, 64, "%lli", opt.number ) ;
      break ;
    case OptionType::FLOAT:
      snprintf( Buffer, 64, "%g", opt.fpval ) ;
      break ;
    case OptionType::STRING:
      return value.c_str() ;
    default:
       Buffer[ 0 ] = '\0' ;
  }
  return Buffer ;
}
