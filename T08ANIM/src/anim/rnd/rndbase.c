/* FILE NAME  : rndbase.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 09.06.2026
 */

#include "rnd.h"

VOID VA6_RndInit( HWND hWnd )
{
  HDC hDC;

  VA6_hRndWnd = hWnd;
  hDC = GetDC(hWnd);
  VA6_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(hWnd, hDC);
    
  VA6_hRndBmFrame = NULL;

  VA6_RndResize(47, 47);
  VA6_RndCamSet(VecSet1(8), VecSet1(0), VecSet(0, 1, 0));
}

VOID VA6_RndClose( VOID )
{
  DeleteObject(VA6_hRndBmFrame);
  DeleteDC(VA6_hRndDCFrame);
}

VOID VA6_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(VA6_hRndWnd);
 
  if (VA6_hRndBmFrame != NULL)
    DeleteObject(VA6_hRndBmFrame);
  VA6_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(VA6_hRndWnd, hDC);
 
  SelectObject(VA6_hRndDCFrame, VA6_hRndBmFrame);
 
  /* сохраняем размеры */
  VA6_RndFrameW = W;
  VA6_RndFrameH = H;
 
  /* пересчитываем проекию */
  VA6_RndProjSet();
}

VOID VA6_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, VA6_RndFrameW, VA6_RndFrameH,
    VA6_hRndDCFrame, 0, 0, SRCCOPY);
}


VOID VA6_RndStart( VOID )
{
  SelectObject(VA6_hRndDCFrame, GetStockObject(DC_BRUSH));
  SetDCBrushColor(VA6_hRndDCFrame, RGB(0, 0, 0));
  Rectangle(VA6_hRndDCFrame, 0, 0, VA6_RndFrameW, VA6_RndFrameH);
}

VOID VA6_RndEnd( VOID )
{
}

VOID VA6_RndProjSet( VOID )
{
  DBL rx, ry;
 
  rx = ry = VA6_RndProjSize;
  /* Correct aspect ratio */
  if (VA6_RndFrameW > VA6_RndFrameH)
    rx *= (DBL)VA6_RndFrameW / VA6_RndFrameH;
  else
    ry *= (DBL)VA6_RndFrameH / VA6_RndFrameW;
  VA6_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      VA6_RndProjDist, VA6_RndProjFarClip);
  VA6_RndMatrVP = MatrMulMatr(VA6_RndMatrView, VA6_RndMatrProj);
}
  
VOID VA6_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  VA6_RndMatrView = MatrView(Loc, At, Up);
  VA6_RndMatrVP = MatrMulMatr(VA6_RndMatrView, VA6_RndMatrProj);
}