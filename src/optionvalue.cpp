
#include "cmdline/optionvalue.h"

#include <sstream>
#include <string.h>


typedef CmdOption::DataHandle DataHandle ;



std::string OptionValue::GetString( void ) const
{
  std::stringstream Out ;
  switch ( Type() )
  {
    case      CMD_INT8_T:
      Out << (int8_t) *this ;
      break ;
    case     CMD_INT16_T:
      Out << (int16_t) *this ;
      break ;
    case     CMD_INT32_T:
      Out << (int32_t) *this ;
      break ;
    case     CMD_INT64_T:
      Out << (int64_t) *this ;
      break ;
    case     CMD_UINT8_T:
      Out << (uint8_t) *this ;
      break ;
    case    CMD_UINT16_T:
      Out << (uint16_t) *this ;
      break ;
    case    CMD_UINT32_T:
      Out << (uint32_t) *this ;
      break ;
    case    CMD_UINT64_T:
      Out << (uint64_t) *this ;
      break ;
    case   CMD_FLOAT32_T:
      Out << (float) *this ;
      break ;
    case   CMD_FLOAT64_T:
      Out << (double) *this ;
      break ;
    case   CMD_FLOAT96_T:
      Out << (long double) *this ;
      break ;
    case    CMD_STRING_T:
      Out << (const char *) *this ;
      break ;
    case      CMD_CHAR_T:
      Out << (char) *this ;
    default: ;
  }
  return Out.str() ;
}



DataHandle* OptionValue::Copy( int Index, const DataHandle *Input )
{
  using namespace __CMD ;
  switch ( Index )
  {
    case CMD_INT16_T:
      return CreateCopy<CMD_INT16_T>( Input ) ;
    case CMD_INT32_T:
      return CreateCopy<CMD_INT32_T>( Input ) ;
    case CMD_INT64_T:
      return CreateCopy<CMD_INT64_T>( Input ) ;
    case CMD_FLOAT32_T:
      return CreateCopy<CMD_FLOAT32_T>( Input ) ;
    case CMD_FLOAT64_T:
      return CreateCopy<CMD_FLOAT64_T>( Input ) ;
    case CMD_FLOAT96_T:
      return CreateCopy<CMD_FLOAT96_T>( Input ) ;
    case CMD_UINT16_T:
      return CreateCopy<CMD_UINT16_T>( Input ) ;
    case CMD_UINT32_T:
      return CreateCopy<CMD_UINT32_T>( Input ) ;
    case CMD_UINT64_T:
      return CreateCopy<CMD_UINT64_T>( Input ) ;
    case CMD_BOOL_T:
      return CreateCopy<CMD_BOOL_T>( Input ) ;
    case CMD_CHAR_T:
      return CreateCopy<CMD_CHAR_T>( Input ) ;
    case CMD_INT8_T:
      return CreateCopy<CMD_INT8_T>( Input ) ;
    case CMD_UINT8_T:
      return CreateCopy<CMD_UINT8_T>( Input ) ;
    case CMD_STRING_T:
    {
      const char *Out = NULL, *In =
        static_cast<const DataItem<const char *>*>(Input) -> Item ;
      if ( In )  Out = strdup( In ) ;
      return new DataItem<const char *>( Out ) ;
    }
    default: ;
  }
  return NULL ;
}



void OptionValue::Discard( const DataHandle *Data )
{
  if ( Data )
  {
    if ( Data -> Type() == CMD_STRING_T )
    {
      const char *String =
       static_cast< const DataItem<const char*> * >(Data) -> Item ;
      if ( String )  free( (void*) String ) ;
    }
    delete Data ;
  }
}



OptionValue::OptionValue( const OptionValue &OV )
{
  Handle = Create( OV.Type(), OV.Handle, this ) ;
}



OptionValue::OptionValue( void ) : CmdOption() {}
OptionValue::~OptionValue( void ) { Destroy( this ) ; }



OptionValue& OptionValue::operator=( const OptionValue &In )
{
  if ( this == &In )  return *this ;
  Destroy( this ) ;
  Handle = Create( In.Type(), In.Handle, this ) ;
  return *this ;
}
