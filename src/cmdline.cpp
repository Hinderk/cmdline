
#include "cmdline/cmdline.h"

#include <sstream>




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
  Data[ 0 ] = {} ;             // account for arguments ...
}



OptionIndex CmdLine::AddOption( const OptionValue &Option          ,
                                const char        *ShortOptionName ,
                                const char        *LongOptionName  ,
                                const char        *NameOfDefault   ,
                                const char        *UnitOfDefault   ,
                                bool               UseDefault      )
{
  if ( TypeSupported( Option.Type() ) )
  {
    if ( ShortOptionName || LongOptionName )
    {
      int &Index = ShortOptionName ?
                   Short[ ShortOptionName ] : Long[ LongOptionName ];
      Index = Index ? Index : ++ NewOption ;
      if ( LongOptionName )  Long[ LongOptionName ] = Index ;
      if ( ShortOptionName )  Short[ ShortOptionName ] = Index ;
      Data[ Index ].Required = false ;
      Data[ Index ].HasDefault = false ;
      if ( Option.Type() != CMD_BOOL_T )
        Data[ Index ].HasDefault = UseDefault ;
      Data[ Index ].Default = Option ;
      Data[ Index ].Info = "" ;
      Data[ Index ].Unit = "" ;
      if ( UnitOfDefault )  Data[ Index ].Unit = UnitOfDefault ;
      if ( NameOfDefault )
        Data[ Index ].Name = NameOfDefault ;
      else
        Data[ Index ].Name = InputType( Option.Type() ) ;
      return OptionIndex( Index ) ;
    }
  }
  return OptionIndex( -1 ) ;       // This option index is invalid!
}



int CmdLine::AddOption( int Type, int First, const char *Name )
{
  if ( First > 0 )
  {
    FirstIndex.insert( First ) ;
    FirstType[ First ] = Type ;
    if ( Name )
      FirstName[ First ] = Name ;
    else
      FirstName[ First ] = InputType( Type ) ;
    return 0 ;
  }
  return CMD_ILLEGAL_ARG_POSITION ;
}



int CmdLine::UseDefault( OptionIndex Option, bool Use, const char *Unit )
{
  if ( Data.count( Option ) > 0 )
  {
    if ( Data[ Option ].Default.Type() != CMD_BOOL_T )
    {
      if ( Unit )  Data[ Option ].Unit = Unit ;
      Data[ Option ].HasDefault = Use ;
      Data[ Option ].Required &= !Use ;
      return 0 ;
    }
    return CMD_ILLEGAL_OPTION_TYPE ;
  }
  return CMD_UNDEFINED_OPTION ;
}



int CmdLine::EnforceOption( OptionIndex Option, bool Enforce )
{
  if ( Data.count( Option ) > 0 )
  {
    if ( Data[ Option ].Default.Type() != CMD_BOOL_T )
    {
      Data[ Option ].Required = Enforce ;
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
      {
        FirstType.erase( i ) ;
        FirstName.erase( i ) ;
      }
    }
    swap( Indices, FirstIndex ) ;
  }
  return 0 ;
}



int CmdLine::AddName( OptionIndex Option, const char *Name )
{
  if ( Option > 0 )
  {
    if ( Data.count( Option ) > 0 )
    {
      if ( Name )  
        Data[ Option ].Name = Name ;
      else
      {
        int Type = Data[ Option ].Default.Type() ;
        Data[ Option ].Name = InputType( Type ) ;
      }
      return 0 ;
    }
    return CMD_UNDEFINED_OPTION ;
  }
  return CMD_ILLEGAL_OPTION_INDEX ;
}



int CmdLine::AddHelp( OptionIndex Option, const char *Text )
{
  if ( Option > 0 )
  {
    if ( Data.count( Option ) > 0 )
    {
      Data[ Option ].Info.clear() ;
      if ( Text )  Data[ Option ].Info = Text ;
      return 0 ;
    }
    return CMD_UNDEFINED_OPTION ;
  }
  return CMD_ILLEGAL_OPTION_INDEX ;
}



int CmdLine::QueryOption( OptionValue &Result, OptionIndex Option )
{
  OptionCounter = (int) Arguments.count( Option ) ;
  if ( OptionCounter > 0 )
  {
    ActiveOption = Option ;
    for ( const auto &a : Arguments )
    {
      if ( a.first == Option )
      {
        Result = a.second ;
        return OptionCounter ;
      }
    }
  }
  if ( Data.count( Option ) )
  {
    if ( Data[ Option ].HasDefault )
    {
      Result = Data[ Option ].Default ;
      OptionCounter = 1 ;
    }
  }
  return OptionCounter ;
}



int CmdLine::NextOption( OptionValue &Result )
{
  if ( OptionCounter > 1 )
  {
    OptionCounter -- ;
    int skip = (int) Arguments.count( ActiveOption ) - OptionCounter ;
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



void CmdLine::SetPreamble( const char *Text )
{
  Preamble.clear() ;
  if ( Text )  Preamble = Text ;
}



void CmdLine::SetEpilogue( const char *Text )
{
  Epilogue.clear() ;
  if ( Text )  Epilogue = Text ;
}



int CmdLine::Help( char *Message, size_t Length ) const
{
  return 0 ;
}



int CmdLine::Usage( char *Message, size_t Length ) const
{
  using namespace std ;
  stringstream Content ;
  map<int,string> sopt, lopt, args ;
  for ( const auto &s : Short )  sopt[ s.second ] = s.first ;
  for ( const auto &l : Long )  lopt[ l.second ] = l.first ;
  size_t pos = Command.find_last_of( "\\/" ) ;
  string Out( "Usage:  " ) ;
  Out += Command.substr( pos + 1 ) ;
  for ( const auto &c : Data )
  {
    string a, o, entry ;
    size_t s = sopt.count( c.first ) ;
    size_t l = lopt.count( c.first ) ;
    if ( !c.second.Required || c.second.HasDefault )  a = '[' ;
    if ( s > 0 )
    {
      entry = sopt[ c.first ] ;
      if ( l > 0 )
      {
        a += '(' ;
        entry += '|' + lopt[ c.first ] ;
        if ( c.second.Default.Type() != CMD_BOOL_T )  entry += '=' ;
        entry += ')' ;
      }
    }
    else if ( l > 0 )
    {
      entry = lopt[ c.first ] ;
      if ( c.second.Default.Type() != CMD_BOOL_T )  entry += '=' ;
    }
    else
      continue ;
    if ( c.second.Default.Type() != CMD_BOOL_T )
    {
      entry += '<' + c.second.Name ;
      if ( c.second.HasDefault )
      {
        entry += ":=" ;
        entry += c.second.Default.GetString() ;
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
      snprintf( Buffer, 64, "-%i>", i - iold ) ;
      Out += " <" + arg + "-1> ... <" ;
      Out += arg + Buffer ;
    }
    else if ( i > iold + 1 )
    {
      Out += " <" + arg + "-1>" ;
      Out += " <" + arg + "-2>" ;
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
    snprintf( Buffer, 64, "-%i>", 1 + LastIndex - iold ) ;
    Out += " <" + arg + "-1> ... <" ;
    Out += arg + Buffer ;
  }
  else if ( iold < LastIndex )
  {
    Out += " <" + arg + "-1>" ;
    Out += " <" + arg + "-2>" ;
  }
  else if ( iold == LastIndex )
    Out += " <" + arg + '>' ;
  else if ( print )
    Out += " <" + arg + "-1> <" + arg + "-2> ..." ;
  Message[ 0 ] = '\0' ;
  if ( Out.size() < Length )
  {
    strncpy( Message, Out.c_str(), Length ) ;
    return 0 ;
  }
  return CMD_BUFFER_SIZE_INSUFFICIENT ;
}



const char* CmdLine::InputType( int TypeIndex ) const
{
  switch ( TypeIndex )
  {
    case      CMD_INT8_T:
    case     CMD_INT16_T:
    case     CMD_INT32_T:
    case     CMD_INT64_T:
    case     CMD_UINT8_T:
    case    CMD_UINT16_T:
    case    CMD_UINT32_T:
    case    CMD_UINT64_T:
      return "number" ;
    case   CMD_FLOAT32_T:
    case   CMD_FLOAT64_T:
    case   CMD_FLOAT96_T:
      return "value" ;
    case    CMD_STRING_T:
      return "string" ;
    case      CMD_CHAR_T:
      return "character" ;
    default: ;
  }
  return "input" ;
}



bool CmdLine::TypeSupported( int TypeIndex ) const
{
  switch ( TypeIndex )
  {
    case      CMD_INT8_T:
    case     CMD_INT16_T:
    case     CMD_INT32_T:
    case     CMD_INT64_T:
    case     CMD_UINT8_T:
    case    CMD_UINT16_T:
    case    CMD_UINT32_T:
    case    CMD_UINT64_T:
    case   CMD_FLOAT32_T:
    case   CMD_FLOAT64_T:
    case   CMD_FLOAT96_T:
    case    CMD_STRING_T:
    case      CMD_CHAR_T:
    case      CMD_BOOL_T:
      return true ;
    default: ;
  }
  return false ;
}



int CmdLine::Insert( int Type, int Index, std::string &sp )
{
  char *end = NULL ;
  errno = 0 ;
  switch ( Type )
  {
    case CMD_INT8_T:
    {
      int64_t i = std::strtoll( sp.c_str(), &end, 10 ) ;
      if ( *end || errno )  return CMD_ILLEGAL_CMDLINE_PARAM ;
      int8_t Value = i ;
      if ( ( i & 0xFF ) == i )
        Arguments.insert( { Index, OptionValue( Value ) } ) ;
      return 0 ;
    }
    case CMD_INT16_T:
    {
      int64_t i = std::strtoll( sp.c_str(), &end, 10 ) ;
      if ( *end || errno )  return CMD_ILLEGAL_CMDLINE_PARAM ;
      int16_t Value = i ;
      if ( ( i & 0xFFFF ) == i )
        Arguments.insert( { Index, OptionValue( Value ) } ) ;
      return 0 ;
    }
    case CMD_INT32_T:
    {
      int64_t i = std::strtoll( sp.c_str(), &end, 10 ) ;
      if ( *end || errno )  return CMD_ILLEGAL_CMDLINE_PARAM ;
      int32_t Value = i ;
      if ( ( i & 0xFFFFFFFF ) == i )
        Arguments.insert( { Index, OptionValue( Value ) } ) ;
      return 0 ;
    }
    case CMD_INT64_T:
    {
      int64_t i = std::strtoll( sp.c_str(), &end, 10 ) ;
      if ( *end || errno )  return CMD_ILLEGAL_CMDLINE_PARAM ;
      Arguments.insert( { Index, OptionValue( i ) } ) ;
      return 0 ;
    }
    case CMD_UINT8_T:
    {
      uint64_t u = std::strtoull( sp.c_str(), &end, 10 ) ;
      if ( *end || errno )  return CMD_ILLEGAL_CMDLINE_PARAM ;
      uint8_t Value = u ;
      if ( ( u & 0xFF ) == u )
        Arguments.insert( { Index, OptionValue( Value ) } ) ;
      return 0 ;
    }
    case CMD_UINT16_T:
    {
      uint64_t u = std::strtoull( sp.c_str(), &end, 10 ) ;
      if ( *end || errno )  return CMD_ILLEGAL_CMDLINE_PARAM ;
      uint16_t Value = u ;
      if ( ( u & 0xFFFF ) == u )
        Arguments.insert( { Index, OptionValue( Value ) } ) ;
      return 0 ;
    }
    case CMD_UINT32_T:
    {
      uint64_t u = std::strtoull( sp.c_str(), &end, 10 ) ;
      if ( *end || errno )  return CMD_ILLEGAL_CMDLINE_PARAM ;
      uint32_t Value = u ;
      if ( ( u & 0xFFFFFFFF ) == u )
        Arguments.insert( { Index, OptionValue( Value ) } ) ;
      return 0 ;
    }
    case CMD_UINT64_T:
    {
      uint64_t u = std::strtoull( sp.c_str(), &end, 10 ) ;
      if ( *end || errno )  return CMD_ILLEGAL_CMDLINE_PARAM ;
      Arguments.insert( { Index, OptionValue( u ) } ) ;
      return 0 ;
    }
    case CMD_FLOAT32_T:
    {
      float fp = std::strtof( sp.c_str(), &end ) ;
      if ( *end || errno )  return CMD_ILLEGAL_CMDLINE_PARAM ;
      Arguments.insert( { Index, OptionValue( fp ) } ) ;
      return 0 ;
    }
    case CMD_FLOAT64_T:
    {
      double fp = std::strtod( sp.c_str(), &end ) ;
      if ( *end || errno )  return CMD_ILLEGAL_CMDLINE_PARAM ;
      Arguments.insert( { Index, OptionValue( fp ) } ) ;
      return 0 ;
    }
    case CMD_FLOAT96_T:
    {
      long double fp = std::strtold( sp.c_str(), &end ) ;
      if ( *end || errno )  return CMD_ILLEGAL_CMDLINE_PARAM ;
      Arguments.insert( { Index, OptionValue( fp ) } ) ;
      return 0 ;
    }
    case CMD_STRING_T:
      Arguments.insert( { Index, OptionValue( sp.c_str() ) } ) ;
      return 0 ;
    case CMD_CHAR_T:
      if ( sp.size() == 1 )
      {
        Arguments.insert( { Index, OptionValue( sp[0] ) } ) ;
        return 0 ;
      }
    default: ;
  }
  return CMD_ILLEGAL_CMDLINE_PARAM ;
}



int CmdLine::Parse( void )
{
  int OptionCounter = 0 ;
  int CurrentIndex = 0 ;
  int CurrentType = CMD_STRING_T ;
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
      if ( Data[ CurrentIndex ].Default.Type() == CMD_BOOL_T )
      {
        Arguments.insert( { CurrentIndex, OptionValue( true ) } ) ;
        CurrentIndex = 0 ;
      }
    }
    else if ( Long.count( s ) )       //  --option value
    {
      CurrentIndex = Long[ s ] ;
      SkipEqualSign = true ;          //  --option = value
      GetValue = false ;
      if ( Data[ CurrentIndex ].Default.Type() == CMD_BOOL_T )
      {
        Arguments.insert( { CurrentIndex, OptionValue( true ) } ) ;
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
      int N = CurrentIndex ;
      int Type = Data[ CurrentIndex ].Default.Type() ;
      switch ( Type )
      {
        case CMD_BOOL_T:
          State = CMD_ILLEGAL_CMDLINE_PARAM ;
          break ;
        case CMD_UNDEFINED_T:
        {
          if ( FirstIndex.count( ++ OptionCounter ) )
            CurrentType = FirstType[ OptionCounter ] ;
          N = 0 ;
          Type = CurrentType ;
        }
        default:
        {
          State = Insert(Type,N,sp) ? CMD_ILLEGAL_CMDLINE_PARAM : State ;
        }
      }
      SkipEqualSign = false ;
      CurrentIndex = 0 ;
    }
  }
  return State ;
}



int CmdLine::CloseBracket( char &c, const char *Expression ) const
{
  const int len = strlen( Expression ) ;
  char Stack[ 16 ] ;
  int sp = 0 ;
  for ( int i = 0 ; i < len ; i++ )
  {
    if ( Expression[i] == '(' )  Stack[ sp ++ ] = ')' ; 
    if ( Expression[i] == '[' )  Stack[ sp ++ ] = ']' ; 
    if ( Expression[i] == '<' )  Stack[ sp ++ ] = '>' ; 
    if ( Expression[i] == ')' && Stack[ -- sp ] != ')' )  return 0 ; 
    if ( Expression[i] == ']' && Stack[ -- sp ] != ']' )  return 0 ; 
    if ( Expression[i] == '>' && Stack[ -- sp ] != '>' )  return 0 ; 
    if ( sp > 8 )  return 0 ;
  }
  c = sp ? Stack[ sp - 1 ] : ' ' ;
  return sp ;
}



int CmdLine::Prettify( char *Out, char *In, size_t Length ) const
{
  const int Size = strlen( In ) ;
  if ( 1 + Size < Length )
  {
    int MaxColumn = 0 ;
    int state = QueryWidth( MaxColumn ) ;
    if ( state )  return state ; 
    memcpy( Out, In, Length ) ;
    char c, *Cursor = strtok( Out, "[(<" ) ;
    int LeftColumn = strlen( Out ) ;
    memset( Out + LeftColumn, 0, Length - LeftColumn ) ;
    int pos = LeftColumn ;
    int column = LeftColumn ;
    int option = 0 ;
    Cursor = strtok( In + pos, ")>]" ) ;
    char *Start = Out + pos ;
    while( Cursor ) 
    {
      int delta = strlen( Cursor ) ;
      if ( Cursor[ 0 ] == ' ' )
      {
        while ( CloseBracket( c, Start ) )
        {
          Out[ pos ++ ] = c ;
          column ++ ;
        } 
        if ( column + 1 > MaxColumn && option > 0 )
        {
          const size_t len = strlen( Start ) ;
          if ( pos + LeftColumn + 3 > Length )
            return CMD_INSUFFICIENT_BUFFERSPACE ;
          memmove( Start + LeftColumn, Start, len ) ;
          memset( Start, ' ', LeftColumn ) ;
          Start[ 0 ] = '\n' ;
          pos += LeftColumn ;
          column = LeftColumn + len ;
        } 
        Start = Out + pos ;
        option ++ ;
      }
      if ( pos + delta + 3 > Length )  return CMD_INSUFFICIENT_BUFFERSPACE ;
      column += delta + 1 ;
      memcpy( Out + pos, Cursor, delta ) ;
      pos += delta ;
      if ( CloseBracket( c, Start ) )  Out[ pos ++ ] = c ;
      Cursor = strtok( NULL, ")>]" ) ;
    }
    while ( CloseBracket( c, Start ) )
    {
      Out[ pos ++ ] = c ;
      column ++ ;
    }
    if ( column + 1 > MaxColumn && option > 0 )
    {
      const size_t len = strlen( Start ) ;
      if ( pos + LeftColumn + 3 > Length )
        return CMD_INSUFFICIENT_BUFFERSPACE ;
      memmove( Start + LeftColumn, Start, len ) ;
      memset( Start, ' ', LeftColumn ) ;
      Start[ 0 ] = '\n' ;
    }
    return 0 ;
  }
  return CMD_INSUFFICIENT_BUFFERSPACE ;
}



#ifdef _WIN32

int CmdLine::QueryWidth( int &CurrentWidth ) const
{
  HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE ) ;
  if ( hConsole != INVALID_HANDLE_VALUE )
  {
    CONSOLE_SCREEN_BUFFER_INFO Info ;
    if ( GetConsoleScreenBufferInfo( hConsole, &Info ) )
    {
      CurrentWidth = Info.dwMaximumWindowSize.X ;
      return 0 ;
    }
    return CMD_CONSOLE_QUERY_FAILED ;
  }
  return CMD_NO_CONSOLE_FOUND ;
}

#else      // _WIN32

int CmdLine::QueryWidth( int &CurrentWidth ) const
{
  winsize W0 ;
  if ( ioctl( STDOUT_FILENO, TIOCGWINSZ, &W0 ) < 0 )
    return CMD_CONSOLE_QUERY_FAILED ;
  CurrentWidth = W0.ws_col ;
  return 0 ;
}

#endif     // _WIN32
