/* FILE NAME  : globe.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 06.06.2026
 */
#include "globe.h"
#include "timer.h"
#include <windows.h>
#include <math.h>
#include <time.h>


static DBL GLB_Ws, GLB_Hs;
static DBL GLB_Wp, GLB_Hp, GLB_ProjSize = 1;
static DBL GLB_ProjDist = 1;

static VEC GLB_Geom[GLB_GRID_H][GLB_GRID_W];
static VEC GLB_GeomN[GLB_GRID_H][GLB_GRID_W];


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

/* Rotate vector around Y axis function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       VEC P;
 *   - rotation angle in degrees:
 *       DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector.
 */
VEC RotateY( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * PI / 180, si = sin(a), co = cos(a);
 
  NewP.X = P.Z * si + P.X * co;
  NewP.Y = P.Y;
  NewP.Z = P.Z * co - P.X * si;
  return NewP;
} /* End of 'RotateY' function */

COLORREF ColorTo255( VEC Color )
{
  INT 
    R = (INT)(Color.X * 255),
    G = (INT)(Color.Y * 255),
    B = (INT)(Color.Z * 255);

  R = GLB_MIN(255, GLB_MAX(0, R));
  G = GLB_MIN(255, GLB_MAX(0, R));
  B = GLB_MIN(255, GLB_MAX(0, R));

  return RGB(R, G, B);
}

VOID GLB_Draw( HDC hDC )
{
  static POINT pnts[GLB_GRID_H][GLB_GRID_W];
  POINT pts[4];
  DBL xp, yp;
  INT s = 2, i, j;
  VEC L = VecNormalize(VecSet(1, 1, 1));
  MATR m;
  DBL t = GLB_Time;

  GLB_Init(0.5);
  GLB_TimerInit();
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SelectObject(hDC, GetStockObject(DC_PEN));

  SetDCPenColor(hDC, RGB(248, 24, 148));
  SetDCBrushColor(hDC, RGB(255, 240, 31));
    
  m = MatrMulMatr(MatrMulMatr(MatrRotateZ(47 * t), MatrRotateY(60 * t)), MatrTranslate(VecSet(0, 0, -3)));
  for (i = 0; i < GLB_GRID_H; i++)
    for (j = 0; j < GLB_GRID_W; j++)
    {
      VEC P = PointTransform(GLB_Geom[i][j], m);

      xp = P.X * GLB_ProjDist / - P.Z;
      yp = P.Y * GLB_ProjDist / - P.Z;
 
      pnts[i][j].x = (INT)(xp * GLB_Ws / GLB_Wp + GLB_Ws / 2);
      pnts[i][j].y = (INT)(- yp * GLB_Hs / GLB_Hp + GLB_Hs / 2);
    }

  /*for (i = 0; i < GLB_GRID_H; i++)
    for (j = 0; j < GLB_GRID_W; j++)
      Ellipse(hDC, pnts[i][j].x - s, pnts[i][j].y - s,
                   pnts[i][j].x + s, pnts[i][j].y + s);  */

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
      VEC N = VectorTransform(GLB_GeomN[i][j], m);
      DBL nl = VecDotVec(N, L);
      VEC C = VecMulNum(VecSet(1, 0.8, 1), nl);

      pts[0] = pnts[i][j];
      pts[1] = pnts[i][j + 1];
      pts[2] = pnts[i + 1][j + 1];
      pts[3] = pnts[i + 1][j];

      SetDCBrushColor(hDC, ColorTo255(C));
      if ((pts[0].x - pts[1].x) * (pts[0].y + pts[1].y) +
          (pts[1].x - pts[2].x) * (pts[1].y + pts[2].y) +
          (pts[2].x - pts[3].x) * (pts[2].y + pts[3].y) +
          (pts[3].x - pts[0].x) * (pts[3].y + pts[0].y) >= 0)
        Polygon(hDC, pts, 4);

    }
}

VOID GLB_Init( DBL R )
{
  INT i, j; 
  DBL t = GLB_Time;
  
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