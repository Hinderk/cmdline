
#include "cmdline.h"




CmdLine::CmdLine( int argc, const char *argv[] ) :

  Command( argv[ 0 ] ) ,
  CommandLine( argv + 1, argv + argc ) ,
  Short() ,
  Long() ,
  Arguments() ,
  Data() ,
  Preamble( "Available Options:\n" ) ,
  Epilogue() ,
  ActiveOption( 0 ) ,
  NewOption( 0 ) ,
  OptionCounter( 0 ) ,
  LastIndex( 0 )
{
  Data[ 0 ].Type = OptionType::NONE ;   // account for arguments ...
}



CmdLine::Option CmdLine::AddOption( OptionType  TypeDesignation ,
                                    const char *ShortOptionName ,
                                    const char *LongOptionName  )
{
  int &Index = Short[ ShortOptionName ] ;
  Index = Index ? Index : ++ NewOption ;
  if ( LongOptionName )  Long[ LongOptionName ] = Index ;
  Data[ Index ].Type = TypeDesignation ;
  Data[ Index ].Required = false ;
  Data[ Index ].HasDefault = false ;
  Data[ Index ].Default = CmdOption() ;
  Data[ Index ].Info = "" ;
  Data[ Index ].Unit = "" ;
  switch ( TypeDesignation )
  {
    case OptionType::INTEGER:
    case OptionType::UNSIGNED:
      Data[ Index ].Name = "number" ;
      break ;
    case OptionType::FLOAT:
      Data[ Index ].Name = "value" ;
      break ;
    case OptionType::STRING:
      Data[ Index ].Name = "string" ;
      break ;
    default:
      Data[ Index ].Name = "" ;
  }
  return Option( Index ) ;
}



int CmdLine::AddDefault( CmdLine::Option  OptionIndex ,
                         const CmdOption &Value       ,
                         const char      *UnitString  )
{
  if ( Value.Type() == OptionType::BOOLEAN )
    return CMD_ILLEGAL_OPTION_TYPE ;
  if ( Data.count( OptionIndex.Index ) > 0 )
  {
    if ( Data[ OptionIndex.Index ].Type == Value.Type() )
    {
      Data[ OptionIndex.Index ].Unit.clear() ;
      if ( UnitString )  Data[ OptionIndex.Index ].Unit = UnitString ;
      Data[ OptionIndex.Index ].Default = Value ;
      Data[ OptionIndex.Index ].HasDefault = true ;
      return 0 ;
    }
    return CMD_ILLEGAL_OPTION_TYPE ;
  }
  return CMD_UNDEFINED_OPTION ;
}



int CmdLine::EnforceOption( CmdLine::Option OI, bool Enforce )
{
  if ( Data.count( OI.Index ) > 0 )
  {
    if ( Data[ OI.Index ].Type != OptionType::BOOLEAN )
    {
      Data[ OI.Index ].Required = Enforce ;
      return 0 ;
    }
    return CMD_ILLEGAL_OPTION_TYPE ;
  }
  return CMD_UNDEFINED_OPTION ;
}



int CmdLine::EnforceOption( int Index, bool Enforce )
{
  if ( Enforce )
    LastIndex = Index > LastIndex ? Index : LastIndex ;
  else if ( Index < LastIndex )
  {
    LastIndex = Index < 1 ? 0 : Index - 1 ;
    std::set<int> Indices ;
    for ( int i : FirstIndex )
    {
      if ( i < Index )
        Indices.insert( i ) ;
      else
        FirstName.erase( i ) ;
    }
    swap( Indices, FirstIndex ) ;
  }
  return 0 ;
}



int CmdLine::AddName( int Position, const char *Name )
{
  if ( Position > 0 )
  {
    if ( Name )
    {
      FirstIndex.insert( Position ) ;
      FirstName[ Position ] = Name ;
    }
    else
    {
      FirstIndex.erase( Position ) ;
      FirstName.erase( Position ) ;
    }
    return 0 ;
  }
  return CMD_ILLEGAL_ARG_POSITION ;
}



int CmdLine::AddName( CmdLine::Option OI, const char *Name )
{
  if ( OI.Index > 0 )
  {
    if ( Data.count( OI.Index ) > 0 )
    {
      if ( Name )
        Data[ OI.Index ].Name = Name ;
      else
        Data[ OI.Index ].Name.clear() ;
      return 0 ;
    }
    return CMD_UNDEFINED_OPTION ;
  }
  return CMD_ILLEGAL_OPTION_INDEX ;
}



int CmdLine::AddHelp( CmdLine::Option OI, const std::string &Text )
{
  if ( OI.Index > 0 )
  {
    if ( Data.count( OI.Index ) > 0 )
    {
      Data[ OI.Index ].Info = Text ;
      return 0 ;
    }
    return CMD_UNDEFINED_OPTION ;
  }
  return CMD_ILLEGAL_OPTION_INDEX ;
}



int CmdLine::QueryOption( CmdOption &Result, CmdLine::Option OI )
{
  OptionCounter = Arguments.count( OI.Index ) ;
  if ( OptionCounter > 0 )
  {
    ActiveOption = OI.Index ;
    for ( const auto &a : Arguments )
    {
      if ( a.first == OI.Index )
      {
        Result = a.second ;
        return OptionCounter ;
      }
    }
  }
  if ( Data.count( OI.Index ) )
  {
    if ( Data[ OI.Index ].HasDefault )
    {
      Result = Data[ OI.Index ].Default ;
      OptionCounter = 1 ;
    }
  }
  return OptionCounter ;
}



int CmdLine::NextOption( CmdOption &Result, CmdLine::Option OI )
{
  if ( OptionCounter > 1 )
  {
    OptionCounter -- ;
    int skip = Arguments.count( ActiveOption ) - OptionCounter ;
    for ( const auto &a : Arguments )
    {
      if ( a.first == ActiveOption && -- skip < 0 )
      {
        Result = a.second ;
        return OptionCounter ;
      }
    }
  }
  return 0 ;
}



std::string CmdLine::Usage( void ) const
{
  using namespace std ;
  map<int,string> sopt, lopt, args ;
  for ( const auto &s : Short )  sopt[ s.second ] = s.first ;
  for ( const auto &l : Long )  lopt[ l.second ] = l.first ;
  size_t pos = Command.find_last_of( "\\/" ) ;
  string Out( "Usage:  " ) ;
  Out += Command.substr( pos + 1 ) ;
  for ( const auto &c : Data )
  {
    string a, o, entry ;
    int s = sopt.count( c.first ) ;
    int l = lopt.count( c.first ) ;
    if ( !c.second.Required || c.second.HasDefault )  a = '[' ;
    if ( s > 0 )
    {
      entry = sopt[ c.first ] ;
      if ( l > 0 )
      {
        a += '(' ;
        entry += '|' + lopt[ c.first ] ;
        if ( c.second.Type != OptionType::BOOLEAN )  entry += '=' ;
        entry += ')' ;
      }
    }
    else if ( l > 0 )
    {
      entry = lopt[ c.first ] ;
      if ( c.second.Type != OptionType::BOOLEAN )  entry += '=' ;
    }
    else
      continue ;
    if ( c.second.Type != OptionType::BOOLEAN )
    {
      entry += '<' + c.second.Name ;
      if ( c.second.HasDefault )
      {
        entry += ":=" ;
        entry += c.second.Default.str() ;
        entry += c.second.Unit ;
      }
      o = '>' ;
    }
    if ( !c.second.Required || c.second.HasDefault )  o += ']' ;
    Out += ' ' + a + entry + o ;
  }
  char Buffer[ 64 ] ;
  string arg( "arg" ) ;
  bool print( false ) ;
  int iold = 1 ;
  for ( int i : FirstIndex )
  {
    print = true ;
    if ( i > iold + 2 )
    {
      snprintf( Buffer, 64, "_%i>", i - iold ) ;
      Out += " <" + arg + "_1> ... <" ;
      Out += arg + Buffer ;
    }
    else if ( i > iold + 1 )
    {
      Out += " <" + arg + "_1>" ;
      Out += " <" + arg + "_2>" ;
    }
    else if ( i > iold )
    {
      Out += " <" + arg + '>' ;
    }
    iold = i ;
    arg = FirstName.at( i ) ;
  }
  if ( iold + 1 < LastIndex )
  {
    snprintf( Buffer, 64, "_%i>", 1 + LastIndex - iold ) ;
    Out += " <" + arg + "_1> ... <" ;
    Out += arg + Buffer ;
  }
  else if ( iold < LastIndex )
  {
    Out += " <" + arg + "_1>" ;
    Out += " <" + arg + "_2>" ;
  }
  else if ( iold == LastIndex )
    Out += " <" + arg + '>' ;
  else if ( print )
    Out += " <" + arg + "_1> <" + arg + "_2> ..." ;
  return Out ;
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
      if ( Data[ CurrentIndex ].Type == OptionType::BOOLEAN )
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
      if ( Data[ CurrentIndex ].Type == OptionType::BOOLEAN )
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
      switch ( Data[ CurrentIndex ].Type )
      {
        case OptionType::BOOLEAN:
          State = CMD_ILLEGAL_CMDLINE_PARAM ;
          break ;
        case OptionType::NONE:
        {
          Arguments.insert( { 0, CmdOption( sp ) } ) ;
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
