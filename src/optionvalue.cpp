
#include "optionvalue.h"
#include <sstream>



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
