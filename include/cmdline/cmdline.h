
#ifndef __CMD_CMDLINE_H
#define __CMD_CMDLINE_H

#include "cmdline/optionparser.h"
#include "cmdline/optionvalue.h"

#include <cstring>
#include <set>
#include <map>
#include <vector>



class CmdLine : public OptionParser {


    struct OptionData {

      bool         Required = false ;
      bool         HasDefault = false ;
      OptionValue  Default ;
      std::string  Info = "" ;
      std::string  Name = "" ;
      std::string  Unit = "" ;

    } ;


  public:

#include "memdebug.h"

    CmdLine( int argc, const char *argv[] ) ;

    void Discard( void )  { delete this ; }

    OptionIndex AddOption( const OptionValue &, const char *, const char * ) ;
    int AddOption( int Type, int First, const char *Name ) ;
    int EnforceOption( OptionIndex Option, bool Enforce ) ;
    int EnforceOption( int LastIndex, bool Enforce ) ;
    int UseDefault( OptionIndex, bool, const char * ) ;
    int AddName( OptionIndex Option, const char *Name ) ;
    int AddHelp( OptionIndex Option, const char *Text ) ;
    int Parse( void ) ;
    int QueryOption( OptionValue &Result, OptionIndex Option ) ;
    int NextOption( OptionValue &Result ) ;

    int Help( char *Message, size_t Length ) const ;
    int Usage( char *Message, size_t Length ) const ;

    void SetPreamble( const char *Text ) ;
    void SetEpilogue( const char *Text ) ;

  private:

    int Insert( int TypeIndex, int Index, std::string &sp ) ;
    const char *InputType( int TypeIndex ) const ;
    bool TypeSupported( int TypeIndex ) const ;

    std::string                             Command ;
    std::vector<std::string>                CommandLine ;
    std::map<std::string,int>               Short ;
    std::map<std::string,int>               Long ;
    std::set<int>                           FirstIndex ;
    std::map<int,std::string>               FirstName ;
    std::map<int,int>                       FirstType ;
    std::multimap<int,OptionValue>          Arguments ;

    std::map<int,OptionData>                Data ;

    std::string                             Preamble ;
    std::string                             Epilogue ;

    int ActiveOption ;
    int NewOption ;
    int OptionCounter ;
    int LastIndex ;

} ;

#endif     // __CMD_CMDLINE_H
