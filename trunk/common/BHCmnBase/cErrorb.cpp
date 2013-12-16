#include "cErrorb.h"
//#include <string.h>
#include <windows.h>  // OutputDebugString()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cErrorb::cErrorb()
{
  d_text[ 0 ] = NULL;
}


cErrorb::~cErrorb()
{
}


cErrorb::cErrorb( const char *pText )
{
  if( pText == NULL )
    lstrcpy( d_text, "Unspecified." );
  else
    lstrcpy( d_text, pText );

  OutputDebugString( "ErrorB: " );
  OutputDebugString( d_text );
  OutputDebugString( "\n" );
}

