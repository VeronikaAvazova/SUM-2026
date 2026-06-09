/* FILE NAME  : rnddata.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 09.06.2026
 */

#include "rnd.h"
HWND VA6_hRndWnd;        /* Work window handle */
HDC VA6_hRndDCFrame;     /* Work window memory device context  */
HBITMAP VA6_hRndBmFrame; /* Work window background bitmap handle */
INT VA6_RndFrameW, VA6_RndFrameH; /* Work window size */

DBL
  VA6_RndProjSize = 0.1,     /* Project plane fit square */
  VA6_RndProjDist = 0.1,     /* Distance to project plane from viewer (near) */
  VA6_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */
 
MATR
  VA6_RndMatrView, /* View coordinate system matrix */
  VA6_RndMatrProj, /* Projection coordinate system matrix */
  VA6_RndMatrVP;   /* Stored (View * Proj) matrix */