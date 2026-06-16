/* FILE NAME  : rndres.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 13.06.2026
 */

#include "rndres.h"
#include "anim/rnd/rnd.h"


VOID VA6_RndResInit( VOID )
{
  VA6_RndShdInit();
}

VOID VA6_RndResClose( VOID )
{            
  VA6_RndShdClose();
}
