
#include "cmdline/optionvalue.h"

#include <sstream>
#include <string.h>



OptionValue::OptionValue( const OptionValue &OV )
{
  Handle = OV.Handle ? OV.Handle -> Copy() : NULL ;
}



OptionValue::OptionValue( void ) : CmdOption() {}


OptionValue::~OptionValue( void )
{
  if ( Handle )  Handle -> Discard() ;
}


OptionValue& OptionValue::operator=( const OptionValue &In )
{
  if ( this == &In )  return *this ;
  if ( Handle )  Handle -> Discard() ;
  Handle = In.Handle ? In.Handle -> Copy() : NULL ;
  return *this ;
}
