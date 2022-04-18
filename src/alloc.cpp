#include <iostream>
#include <stdlib.h>

#include "cmdline/cmdexport.h"



CMDLINE_EXPORT FILE *Log = fopen( "memalloc.log", "w" ) ;



/*

void* operator new( size_t size )
{
  if ( Log == NULL )  Log = fopen( "memalloc.log", "w" ) ;
  void *ptr = malloc( size ) ;
  fprintf( Log, "dll >> %p, %lu\n", ptr, size ) ;
  return ptr ;
}


void* operator new[]( size_t size )
{
  if ( Log == NULL )  Log = fopen( "memalloc.log", "w" ) ;
  void *ptr = malloc( size ) ;
  fprintf( Log, "DLL >> %p, %lu\n", ptr, size ) ;
  return ptr ;
}




void operator delete( void *ptr )
{
  if ( Log == NULL )  Log = fopen( "memalloc.log", "w" ) ;
  fprintf( Log, "dll >> %p\n", ptr ) ;
  free( ptr ) ;
}

*/
