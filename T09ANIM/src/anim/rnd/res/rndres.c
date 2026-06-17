/* FILE NAME  : rndres.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 13.06.2026
 */

#include "rndres.h"
#include "anim/rnd/rnd.h"


VOID VA6_RndResInit( VOID )
{
  VA6_RndShdInit();
  VA6_RndTexInit();  
  VA6_RndMtlInit();
}

VOID VA6_RndResClose( VOID )
{            
  VA6_RndMtlClose();
  VA6_RndTexClose();  
  VA6_RndShdClose();
}
