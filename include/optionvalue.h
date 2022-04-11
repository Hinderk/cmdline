
#ifndef __CMD_OPTIONVALUE_H
#define __CMD_OPTIONVALUE_H

#include <cstdint>
#include <string>
#include <string.h>

#include "cmdoption.h"


#define __TD(N,T) TypeDefinition< N > { typedef T Type ; }
 

namespace __CMD {

  template < int n > struct TypeDefinition { typedef void Type ; } ;

  template<> struct __TD( CMD_INT16_T, int16_t ) ;
  template<> struct __TD( CMD_INT32_T, int32_t ) ;
  template<> struct __TD( CMD_INT64_T, int64_t ) ;
  template<> struct __TD( CMD_FLOAT32_T, float ) ;
  template<> struct __TD( CMD_FLOAT64_T, double ) ;
  template<> struct __TD( CMD_FLOAT96_T, long double ) ;
  template<> struct __TD( CMD_UINT16_T, uint16_t ) ;
  template<> struct __TD( CMD_UINT32_T, uint32_t ) ;
  template<> struct __TD( CMD_UINT64_T, uint64_t ) ;
  template<> struct __TD( CMD_BOOL_T, bool ) ;
  template<> struct __TD( CMD_CHAR_T, char ) ;
  template<> struct __TD( CMD_INT8_T, int8_t ) ;
  template<> struct __TD( CMD_UINT8_T, uint8_t ) ;
  template<> struct __TD( CMD_STRING_T, const char * ) ;

}      // end of namespace __CMD



class OptionValue : public CmdOption {


    template < int Index >
    using DataType = typename __CMD::TypeDefinition< Index >::Type ;


  public:

    OptionValue( const char Text[] )
    {
      DataHandle *Item = new DataItem<const char *>( Text ) ;
      Handle = Copy( CMD_STRING_T, Item ) ;
      delete Item ; 
    }

    template < typename T > OptionValue( const T &val )
    {
      DataHandle *Item = new DataItem<T>( val ) ;
      Handle = Copy( __CMD::TypeIndex<T>::value, Item ) ;
      delete Item ; 
    } 
      
    OptionValue( const CmdOption &CO )
    { 
      Handle = Copy( CO.Type(), CO.Handle ) ;
    }

    OptionValue( const OptionValue &OV )
    {
      Handle = Copy( OV.Type(), OV.Handle ) ;
    }

    OptionValue( void ) : CmdOption() {} 
   ~OptionValue( void ) { Discard( Handle ) ; }


    OptionValue& operator=( const OptionValue &In )
    {
      if ( this == &In )  return *this ;
      Discard( Handle ) ; 
      Handle = Copy( In.Type(), In.Handle ) ;
      return *this ;
    }

    std::string GetString( void ) const ;

  private:

    template < typename T >
    DataHandle* CopyItem( const DataHandle *In )
    {
      return new DataItem<T>(static_cast<const DataItem<T>*>(In)->Item) ;
    }

    template < int Index >
    DataHandle* CreateCopy( const DataHandle *Input )
    {
      return CopyItem< DataType<Index> > ( Input ) ;
    }


    virtual void Discard( const DataHandle *Data )
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


    virtual DataHandle* Copy( int Index, const DataHandle *Input )
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

} ;

#undef __TD


#endif     // __CMD_OPTIONVALUE_H
