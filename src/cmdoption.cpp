
#include "cmdoption.h"



CmdOption::CmdOption( void ) :

  type( OptionType::BOOLEAN ) ,
  value() ,
  opt( {} ) {}



CmdOption::CmdOption( const char *name ) :

  type( OptionType::STRING ) ,
  value( name ) ,
  opt( {} ) {}



CmdOption::CmdOption( const std::string &name ) :

  type( OptionType::STRING ) ,
  value( name ) ,
  opt( {} ) {}
