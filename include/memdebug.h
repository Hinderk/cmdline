


void* operator new( size_t size )
{
  void *ptr = ::operator new( size ) ;
#ifdef __CMD_MAIN
  fprintf( Log, "+ main > %p : %lu\n", ptr, size ) ;
#else
  fprintf( Log, "+  dll > %p : %lu\n", ptr, size ) ;
#endif
  return ptr ;
}


void* operator new[]( size_t size )
{
  void *ptr = ::operator new[]( size ) ;
#ifdef __CMD_MAIN
  fprintf( Log, "+ main > %p : %lu\n", ptr, size ) ;
#else
  fprintf( Log, "+  dll > %p : %lu\n", ptr, size ) ;
#endif
  return ptr ;
}




void operator delete( void *ptr )
{
#ifdef __CMD_MAIN
  fprintf( Log, "- main > %p\n", ptr ) ;
#else
  fprintf( Log, "-  dll > %p\n", ptr ) ;
#endif
  free( ptr ) ;
}
