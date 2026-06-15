
/* FILE NAME  : rnddata.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 09.06.2026
 */

#include "rnd.h"
HWND VA6_hRndWnd;        /* Work window handle */
HDC VA6_hRndDC;     /* Work window memory device context  */
INT VA6_RndFrameW, VA6_RndFrameH; /* Work window size */
HGLRC VA6_hRndGLRC; /* OpenGL rendering context */

DBL
  VA6_RndProjSize = 0.1,     /* Project plane fit square */
  VA6_RndProjDist = 0.1,     /* Distance to project plane from viewer (near) */
  VA6_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */
 
MATR
  VA6_RndMatrView, /* View coordinate system matrix */
  VA6_RndMatrProj, /* Projection coordinate system matrix */
  VA6_RndMatrVP;   /* Stored (View * Proj) matrix */