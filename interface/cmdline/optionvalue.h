
#ifndef __CMD_OPTIONVALUE_H
#define __CMD_OPTIONVALUE_H

#include <string>

#include "cmdline/cmdexport.h"
#include "cmdline/cmdoption.h"



class CMDLINE_EXPORT OptionValue : public CmdOption {

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

   //  Handle = new DataItem<T>( val ) ;
    }

    OptionValue( const OptionValue &OV ) ;
    OptionValue( void ) ;
   ~OptionValue( void ) ;

    OptionValue& operator=( const OptionValue &OV ) ;

    std::string GetString( void ) const ;

  private:

    CMDLINE_NO_EXPORT void Discard( const DataHandle * ) ;
    CMDLINE_NO_EXPORT DataHandle* Copy( int, const DataHandle * ) ;

} ;


#endif     // __CMD_OPTIONVALUE_H
