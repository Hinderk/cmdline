#!/usr/bin/awk -f

BEGIN {
  Counter = 0 
}


/\+ main/ {
  L[ Counter ++ ] = $4 ;
  M[ $4 ] += 1 
}
/\- main/ {
  L[ Counter ++ ] = $4 ;
  M[ $4 ] -= 1 
}

/\+  dll/ {
  L[ Counter ++ ] = $4 ;
  D[ $4 ] += 1 
}
/\-  dll/ {
  L[ Counter ++ ] = $4 ;
  D[ $4 ] -= 1 
}


END {
  for ( i = 0 ; i < Counter ; i++ )
  {
    n = L[ i ]
    print n, M[ n ], D[ n ]
  }
}
