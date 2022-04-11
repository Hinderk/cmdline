
#ifndef __CMD_OPTIONVALUE_H
#define __CMD_OPTIONVALUE_H

#include <string>
#include "cmdoption.h"



class OptionValue : public CmdOption {

  public:

    OptionValue( const char Text[] )
    {
      const DataItem<const char *> Item( Text ) ;
      Handle = Create( CMD_STRING_T, &Item, this ) ;
    }

    template < typename T > OptionValue( const T &val )
    {
      const DataItem<T> Item( val ) ;
      Handle = Create( __CMD::TypeIndex<T>::value, &Item, this ) ;
    } 
      
    OptionValue( const OptionValue &OV ) ;
    OptionValue( void ) ; 
   ~OptionValue( void ) ;

    OptionValue& operator=( const OptionValue &In ) ;

    std::string GetString( void ) const ;

  private:

    void Discard( const DataHandle *Data ) ;
    DataHandle* Copy( int Index, const DataHandle *Input ) ;

} ;


#endif     // __CMD_OPTIONVALUE_H
