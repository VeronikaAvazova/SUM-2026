/* FILE NAME  : anim.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 11.06.2026
 */

#include "anim.h"

VOID VA6_AnimInit( HWND hWnd )
{

}

VOID VA6_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < VA6_Anim.NumOfUnits; i++)
  {
    VA6_Anim.Units[i]->Close(VA6_Anim.Units[i], &VA6_Anim);
    free(VA6_Anim.Units[i]);
  }
  VA6_Anim.NumOfUnits = 0;
  VA6_RndClose();
}

VOID VA6_AnimResize( INT W, INT H );
VOID VA6_AnimCopyFrame( HDC hDC );
VOID VA6_AnimRender( VOID );
VOID VA6_AnimAddUnit( va6UNIT *Uni );
VOID VA6_AnimFlipFullScreen( VOID );
VOID VA6_AnimExit( VOID );

VOID VA6_AnimUnitAdd( va6UNIT *Uni )
{
  if (VA6_Anim.NumOfUnits < VA6_MAX_UNITS)
    VA6_Anim.Units[VA6_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &VA6_Anim);
}