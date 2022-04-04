
#ifndef __SMR_CMDLINE_H
#define __SMR_CMDLINE_H

#include <cmdoption.h>
#include <map>
#include <vector>


#define CMD_UNDEFINED_OPTION 3300
#define CMD_ILLEGAL_CMDLINE_PARAM 3310




class CmdLine {

  public:

    CmdLine( int argc, const char *argv[] ) ;

    int AddOption( OptionType, const char *, const char * = NULL ) ;
    int AddDefault( int OptionIndex, const CmdOption &Option ) ;
    int Parse( void ) ;
    int QueryOption( CmdOption &Result, int OptionIndex = 0 ) ;
    int NextOption( CmdOption &Result, int OptionIndex = 0 ) ;

  private:

    std::multimap<int,CmdOption>::iterator  Cursor ;
    std::vector<std::string>                CommandLine ;
    std::map<std::string,int>               Short ;
    std::map<std::string,int>               Long ;
    std::map<int,OptionType>                Type ;
    std::map<int,CmdOption>                 Default ;
    std::multimap<int,CmdOption>            Arguments ;

    int NewOption ;
    int OptionCounter ;

} ;

#endif     // __SMR_CMDLINE_H
