/* FILE NAME  : rndprim.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 09.06.2026
 */

#include "rnd.h"

VOID VA6_RndPrimFree( va6PRIM *Pr )
{
  free(Pr->V);
  memset(Pr, 0, sizeof(va6VERTEX));   /* <-- <string.h>, WinAPI, ZeroMemory */
}
 
 
BOOL VA6_RndPrimCreate( va6PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;
 
  memset(Pr, 0, sizeof(va6PRIM));
  size = sizeof(va6VERTEX) * NoofV + sizeof(INT) * NoofI;
 
  if ((Pr->V = malloc(size)) == NULL)
    return FALSE;
  Pr->I = (INT *)(Pr->V + NoofV);
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  Pr->Trans = MatrIdentity();
  memset(Pr->V, 0, size);
  return TRUE;
}
 
VOID VA6_RndPrimDraw( va6PRIM *Pr, MATR World )
{
  INT i;
  MATR wvp = MatrMulMatr3(Pr->Trans, World, VA6_RndMatrVP);
  POINT *pnts;
 
  if ((pnts = malloc(sizeof(POINT) * Pr->NumOfV)) == NULL)
    return;
 
  /* Build vertex projects */
  for (i = 0; i < Pr->NumOfV; i++)
  {
    VEC p = VecMulMatr(Pr->V[i].P, wvp);
 
 
    pnts[i].x = (INT)((p.X + 1) * VA6_RndFrameW / 2);
    pnts[i].y = (INT)((-p.Y + 1) * VA6_RndFrameH / 2);
  }
  SelectObject(VA6_hRndDCFrame, GetStockObject(DC_PEN));
  SetDCPenColor(VA6_hRndDCFrame, RGB(200, 30, 30));
  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    MoveToEx(VA6_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y, NULL); 
    LineTo(VA6_hRndDCFrame, pnts[Pr->I[i + 1]].x, pnts[Pr->I[i + 1]].y);
    LineTo(VA6_hRndDCFrame, pnts[Pr->I[i + 2]].x, pnts[Pr->I[i + 2]].y);
    LineTo(VA6_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y);
  }
  free(pnts);
}