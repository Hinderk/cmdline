
#ifndef __CMD_CMDLINE_H
#define __CMD_CMDLINE_H

#include <cmdoption.h>
#include <set>
#include <map>
#include <vector>


#define CMD_UNDEFINED_OPTION 8000
#define CMD_ILLEGAL_OPTION_TYPE 8010
#define CMD_ILLEGAL_CMDLINE_PARAM 8020
#define CMD_ILLEGAL_ARG_POSITION 8030
#define CMD_ILLEGAL_OPTION_INDEX 8040



class CmdLine {

    struct OptionData {

      bool         Required = false ;
      bool         HasDefault = false ;
      OptionType   Type = OptionType::NONE ;
      CmdOption    Default = {} ;
      std::string  Info = "" ;
      std::string  Name = "" ;
      std::string  Unit = "" ;

    } ;

  public:

    class Option {

      friend class CmdLine ;

      Option( int n ) : Index( n ) {}
      int Index ;

    } ;

    CmdLine( int argc, const char *argv[] ) ;

    Option AddOption( OptionType, const char *, const char * = NULL ) ;
    int AddOption( OptionType Type, int FirstIndex ) ;
    int EnforceOption( Option Index, bool Enforce = true ) ;
    int EnforceOption( int LastIndex, bool Enforce = true ) ;
    int AddDefault( Option, const CmdOption &, const char * = NULL ) ;
    int AddName( int FirstIndex, const char *Name = NULL ) ;
    int AddName( Option Index, const char *Name ) ;
    int AddHelp( Option Index, const std::string &Text ) ;
    int Parse( void ) ;
    int QueryOption( CmdOption &Result, Option Index = 0 ) ;
    int NextOption( CmdOption &Result, Option Index = 0 ) ;

    std::string Help( void ) const ;
    std::string Usage( void ) const ;

    void SetPreamble( const std::string &Text ) ;
    void SetEpilogue( const std::string &Text ) ;

  private:

    std::string                             Command ;
    std::vector<std::string>                CommandLine ;
    std::map<std::string,int>               Short ;
    std::map<std::string,int>               Long ;
    std::set<int>                           FirstIndex ;
    std::map<int,std::string>               FirstName ;
    std::multimap<int,CmdOption>            Arguments ;

    std::map<int,OptionData>                Data ;

    std::string                             Preamble ;
    std::string                             Epilogue ;

    int ActiveOption ;
    int NewOption ;
    int OptionCounter ;
    int LastIndex ;

} ;

#endif     // __CMD_CMDLINE_H
