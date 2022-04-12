
#ifndef __CMD_OPTIONPARSER_H
#define __CMD_OPTIONPARSER_H

#include "cmdline/optionvalue.h"

#define CMD_UNDEFINED_OPTION 8000
#define CMD_ILLEGAL_OPTION_TYPE 8010
#define CMD_ILLEGAL_CMDLINE_PARAM 8020
#define CMD_ILLEGAL_ARG_POSITION 8030
#define CMD_ILLEGAL_OPTION_INDEX 8040
#define CMD_BUFFER_SIZE_INSUFFICIENT 8050

class CmdLine ;
class OptionParser ;


class OptionIndex {

  friend class OptionParser ;
  friend class CmdLine ;

  OptionIndex( int n ) : Index( n ) {}
  int Index ;

} ;


extern "C" {

  CMDLINE_EXPORT OptionParser *
    CreateOptionParser( int argc, const char *argv[] ) ;
  CMDLINE_EXPORT void DestroyOptionParser( OptionParser *Parser ) ;

}


class OptionParser {

  public:

    virtual ~OptionParser( void ) = default ;

    virtual void Discard( void ) = 0 ;

    virtual OptionIndex
      AddOption( const OptionValue &, const char *, const char * = NULL ) = 0 ;
    virtual int AddOption( int, int, const char * = NULL ) = 0 ;
    virtual int EnforceOption( OptionIndex, bool = true ) = 0 ;
    virtual int EnforceOption( int, bool = true ) = 0 ;
    virtual int UseDefault( OptionIndex, bool, const char * = NULL ) = 0 ;
    virtual int AddName( OptionIndex, const char * = NULL ) = 0 ;
    virtual int AddHelp( OptionIndex, const char * = NULL ) = 0 ;
    virtual int Parse( void ) = 0 ;
    virtual int QueryOption( OptionValue &, OptionIndex = 0 ) = 0 ;
    virtual int NextOption( OptionValue & ) = 0 ;

    virtual int Help( char *Message, size_t Length ) const = 0 ;
    virtual int Usage( char *Message, size_t Length ) const = 0 ;

    virtual void SetPreamble( const char *Text = NULL ) = 0 ;
    virtual void SetEpilogue( const char *Text = NULL ) = 0 ;

} ;

#endif     // __CMD_OPTIONPARSER_H
