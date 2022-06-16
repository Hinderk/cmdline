
#ifndef __CMD_OPTIONVALUE_H
#define __CMD_OPTIONVALUE_H

#include <string>

#include "cmdline/cmdexport.h"
#include "cmdline/cmdoption.h"



class CMDLINE_EXPORT OptionValue : public CmdOption {

  public:

    OptionValue( const char Text[] )
    {
      Handle = new __CMD::DataItem<const char *>( Text ) ;
    }

    template < typename T > OptionValue( const T &val )
    {
      Handle = new __CMD::DataItem<T>( val ) ;
    }

    OptionValue( const OptionValue &OV ) ;
    OptionValue( void ) ;
   ~OptionValue( void ) ;

    OptionValue& operator=( const OptionValue &OV ) ;

} ;


#endif     // __CMD_OPTIONVALUE_H
