
#include "cmdline.h"




CmdLine::CmdLine( int argc, const char *argv[] ) :

  CommandLine( argv + 1, argv + argc ) ,
  Short() ,
  Long() ,
  Type() ,
  Default() ,
  Arguments() ,
  NewOption( 0 ) ,
  OptionCounter( 0 )
{
  Type[ 0 ] = OptionType::NONE ;
}



int CmdLine::AddOption( OptionType OT, const char *sopt, const char *lopt )
{
  int &Index = Short[ sopt ] ;
  Index = Index ? Index : ++ NewOption ;
  if ( lopt )  Long[ lopt ] = Index ;
  Type[ Index ] = OT ;
  return Index ;
}



int CmdLine::AddDefault( int OptionIndex, const CmdOption &Option )
{
  if ( Type.count( OptionIndex ) > 0 )
  {
    Default[ OptionIndex ] = Option ;
    return 0 ;
  }
  return CMD_UNDEFINED_OPTION ;
}



int CmdLine::QueryOption( CmdOption &Result, int OptionIndex )
{
  OptionCounter = Arguments.count( OptionIndex ) ;
  if ( OptionCounter > 0 )
  {
    Cursor = Arguments.begin() ;
    while ( Cursor != Arguments.end() )
    {
      if ( Cursor -> first == OptionIndex )
      {
        Result = Cursor -> second ;
        return OptionCounter ;
      }
      ++ Cursor ;
    }
  }
  int Counter = Default.count( OptionIndex ) ;
  if ( Counter > 0 )  Result = Default[ OptionIndex ] ;
  return Counter ;
}



int CmdLine::NextOption( CmdOption &Result, int OptionIndex )
{
  if ( OptionCounter > 0 )
  {
    OptionCounter -- ;
    while ( ++ Cursor != Arguments.end() )
    {
      if ( Cursor -> first == OptionIndex )
      {
        Result = Cursor -> second ;
        return OptionCounter ;
      }
    }
  }
  return 0 ;
}



int CmdLine::Parse( void )
{
  int CurrentIndex = 0 ;
  int State = 0 ;
  bool SkipEqualSign = false ;
  char *end = NULL ;
  Arguments.clear() ;
  for ( const auto &s : CommandLine )
  {
    size_t pos = s.find_first_of( '=' ) ;
    std::string sa = s.substr( 0, 2 ) ;
    std::string sp = s.substr( 0, pos ) ;
    bool GetValue = true ;
    if ( sp.empty() && SkipEqualSign )
    {
      SkipEqualSign = false ;
      sp = s.substr( 1 ) ;
      if ( sp.empty() )  continue ;
    }
    else if ( Short.count( s ) )      //  -o value
    {
      CurrentIndex = Short[ s ] ;
      GetValue = false ;
      if ( Type[ CurrentIndex ] == OptionType::BOOLEAN )
      {
        Arguments.insert( { CurrentIndex, CmdOption( true ) } ) ;
        CurrentIndex = 0 ;
      }
    }
    else if ( Long.count( s ) )       //  --option value
    {
      CurrentIndex = Long[ s ] ;
      SkipEqualSign = true ;          //  --option = value
      GetValue = false ;
      if ( Type[ CurrentIndex ] == OptionType::BOOLEAN )
      {
        Arguments.insert( { CurrentIndex, CmdOption( true ) } ) ;
        CurrentIndex = 0 ;
      }
    }
    else if ( Long.count( sp ) )      //  --option=value
    {
      CurrentIndex = Long[ sp ] ;
      sp = s.substr( ++ pos ) ; 
      GetValue = sp.size() > 0 ;      //  --option= value
    }
    else if ( Short.count( sa ) )     //  -ovalue
    {
      CurrentIndex = Short[ sa ] ;
      sp = s.substr( 2 ) ; 
    }
    else
      sp = s ;
    if ( GetValue )
    {
      switch ( Type[ CurrentIndex ] )
      {
        case OptionType::BOOLEAN:
          State = CMD_ILLEGAL_CMDLINE_PARAM ;
          break ;
        case OptionType::NONE:
        {
          Arguments.insert( { 0, CmdOption( sp.c_str() ) } ) ;
          break ;
        }
        case OptionType::INTEGER:
        {
          int64_t i = std::strtoll( sp.c_str(), &end, 10 ) ;
          if ( *end )
            State = CMD_ILLEGAL_CMDLINE_PARAM ;
          else
            Arguments.insert( { CurrentIndex, CmdOption( i ) } ) ;
          break ;
        }
        case OptionType::FLOAT:
        {
          double val = std::strtod( sp.c_str(), &end ) ;
          if ( *end )
            State = CMD_ILLEGAL_CMDLINE_PARAM ;
          else
            Arguments.insert( { CurrentIndex, CmdOption( val ) } ) ;
          break ;
        }
        case OptionType::UNSIGNED:
        {
          int64_t i = std::strtoll( sp.c_str(), &end, 10 ) ;
          uint64_t nr( i ) ;
          if ( *end || i < 0 )
            State = CMD_ILLEGAL_CMDLINE_PARAM ;
          else
            Arguments.insert( { CurrentIndex, CmdOption( nr ) } ) ;
          break ;
        }
        case OptionType::STRING:
        {
          Arguments.insert( { CurrentIndex, CmdOption( sp ) } ) ;
          break ;
        }
      }
      SkipEqualSign = false ;
      CurrentIndex = 0 ;
    }
  }
  return State ;
}
