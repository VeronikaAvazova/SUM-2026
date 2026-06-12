/* FILE NAME  : anim.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 11.06.2026
 */

#include <string.h>
#include "anim.h"

va6ANIM VA6_Anim;

VOID VA6_AnimInit( HWND hWnd )
{
  memset(&VA6_Anim, 0, sizeof(va6ANIM));

  VA6_Anim.hWnd = hWnd;
  VA6_RndInit(hWnd);
  VA6_Anim.hDC = VA6_hRndDC;
  VA6_Anim.W = VA6_RndFrameW;
  VA6_Anim.H = VA6_RndFrameH;

  VA6_TimerInit();
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

VOID VA6_AnimResize( INT W, INT H )
{
  VA6_RndResize(W, H);
  VA6_Anim.W = W;
  VA6_Anim.H = H;
}

VOID VA6_AnimCopyFrame( VOID )
{
  VA6_RndCopyFrame();
}

VOID VA6_AnimRender( VOID )
{
  INT i;

  VA6_TimerResponse();

  for (i = 0; i < VA6_Anim.NumOfUnits; i++)
    VA6_Anim.Units[i]->Response(VA6_Anim.Units[i], &VA6_Anim);

  VA6_RndStart();
  for (i = 0; i < VA6_Anim.NumOfUnits; i++)
    VA6_Anim.Units[i]->Render(VA6_Anim.Units[i], &VA6_Anim);
  VA6_RndEnd();
}

VOID VA6_AnimFlipFullScreen( VOID );

VOID VA6_AnimDoExit( VOID )
{
  static BOOL IsFinalizeStart = FALSE;

  if (IsFinalizeStart)
    return;
  IsFinalizeStart = TRUE;
  if (MessageBox(VA6_Anim.hWnd, "Are you sure want to exit?",
      "Exit", MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON1) != IDOK)
  {
    IsFinalizeStart = FALSE;
    return;
  }
  PostMessage(VA6_Anim.hWnd, WM_CLOSE, 0, 0);
}

VOID VA6_AnimAddUnit( va6UNIT *Uni )
{
  if (VA6_Anim.NumOfUnits < VA6_MAX_UNITS)
    VA6_Anim.Units[VA6_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &VA6_Anim);
}