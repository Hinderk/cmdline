
#include "cmdline/cmdline.h"



extern "C" {


  OptionParser* CreateOptionParser( int argc, const char *argv[] )
  {
    return new CmdLine( argc, argv ) ;
  }


  void DestroyOptionParser( OptionParser *Parser )
  {
    delete Parser ;
  }


}
