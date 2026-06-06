/* FILE NAME  : globe.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 06.06.2026
 */
#include "globe.h"
#include <windows.h>
#include <math.h>
#include <time.h>

VOID GLB_Resize( INT Ws, INT Hs )
{
  GLB_Ws = Ws;
  GLB_Hs = Hs;

  if (Ws >= Hs)
    GLB_Wp = GLB_ProjSize * Ws / Hs, GLB_Hp = GLB_ProjSize;
  else
    GLB_Wp = GLB_ProjSize, GLB_Hp = GLB_ProjSize * Hs / Ws;
}

/* Rotate vector around Z axis function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       VEC P;
 *   - rotation angle in degrees:
 *       DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector.
 */
VEC RotateZ( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * PI / 180, si = sin(a), co = cos(a);
 
  NewP.X = P.X * co - P.Y * si;
  NewP.Y = P.X * si + P.Y * co;
  NewP.Z = P.Z;
  return NewP;
} /* End of 'RotateZ' function */

/* Rotate vector around X axis function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       VEC P;
 *   - rotation angle in degrees:
 *       DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector.
 */
VEC RotateX( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * PI / 180, si = sin(a), co = cos(a);
 
  NewP.X = P.X;
  NewP.Y = P.Y * co - P.Z * si;
  NewP.Z = P.Y * si + P.Z * co;
  return NewP;
} /* End of 'RotateX' function */

VOID GLB_Draw( HDC hDC )
{
  static POINT pnts[GLB_GRID_H][GLB_GRID_W];
  POINT pts[4];
  DBL len;
  INT s = 2, i, j;  

  GLB_Init(0.3);
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SelectObject(hDC, GetStockObject(DC_PEN));

  SetDCPenColor(hDC, RGB(248, 24, 148));
  SetDCBrushColor(hDC, RGB(255, 240, 31));
    
  for (i = 0; i < GLB_GRID_H; i++)
    for (j = 0; j < GLB_GRID_W; j++)
    {
      VEC P = GLB_Geom[i][j];

      P = RotateX(P, 45);
      pnts[i][j].x = (INT)(P.X * GLB_Ws / GLB_Wp + GLB_Ws / 2);
      pnts[i][j].y = (INT)(- P.Y * GLB_Hs / GLB_Hp + GLB_Hs / 2);
    }

  for (i = 0; i < GLB_GRID_H; i++)
    for (j = 0; j < GLB_GRID_W; j++)
      Ellipse(hDC, pnts[i][j].x - s, pnts[i][j].y - s,
                   pnts[i][j].x + s, pnts[i][j].y + s);

  for (i = 0; i < GLB_GRID_H; i++)
  {
    MoveToEx(hDC, pnts[i][0].x, pnts[i][0].y, NULL);
    for (j = 1; j < GLB_GRID_W; j++)
      LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
  }

  for (j = 1; j < GLB_GRID_W; j++)
  {
    MoveToEx(hDC, pnts[0][j].x, pnts[0][j].y, NULL);
    for (i = 0; i < GLB_GRID_H; i++)
      LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
  }

  for (i = 0; i < GLB_GRID_H - 1; i++)
    for (j = 0; j < GLB_GRID_W - 1; j++)
    {
      VEC N = GLB_GeomN[i][j], L;
      DBL nl = N.X * L.X + N.Y * L.Y + N.Z * L.Z;
      VEC C = {0.47 * nl, 0.8 * nl, 0.30 * nl};

      L.X = 1;
      L.Y = 1;
      L.Z = 1;
      len = sqrt(L.X * L.X + L.Y * L.Y + L.Z * L.Z);
      L.X /= len;
      L.Y /= len;
      L.Z /= len;

      if ((pts[0].x - pts[1].x) * (pts[0].y - pts[1].y) +
          (pts[1].x - pts[2].x) * (pts[1].y - pts[2].y) +
          (pts[2].x - pts[3].x) * (pts[2].y - pts[3].y) +
          (pts[3].x - pts[0].x) * (pts[3].y - pts[4].y) <= 0)
        Polygon(hDC, pts, 4);
    }
}

VOID GLB_Init( DBL R )
{
  INT i, j; 
  DBL t = 0.03 * clock() / (DBL)CLOCKS_PER_SEC;
  
  for (i = 0; i < GLB_GRID_H; i++)
    for (j = 0; j < GLB_GRID_W; j++)
    {
      DBL theta = i * PI / (GLB_GRID_H - 1), phi = j * 2 * PI / (GLB_GRID_W - 1);
 
      GLB_Geom[i][j].X = R * sin(theta) * sin(phi + t);
      GLB_Geom[i][j].Y = R * cos(theta);
      GLB_Geom[i][j].Z = R * sin(theta) * cos(phi + t);
      
      GLB_GeomN[i][j].X = sin(theta) * sin(phi + t);
      GLB_GeomN[i][j].Y = cos(theta);
      GLB_GeomN[i][j].Z = sin(theta) * cos(phi + t);
    
    }
}