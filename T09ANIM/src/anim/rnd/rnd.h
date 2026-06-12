/* FILE NAME: rnd.h
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: VA6
 * DATE: 09.06.2026
 */

#define GLEW_STATIC
#include "glew.h"

#include "def.h"

extern HWND VA6_hRndWnd;        /* Work window handle */
extern HDC VA6_hRndDC;     /* Work window memory device context  */
extern INT VA6_RndFrameW, VA6_RndFrameH; /* Work window size */
extern HGLRC VA6_hRndGLRC;

extern DBL
  VA6_RndProjSize,     /* Project plane fit square */
  VA6_RndProjDist,     /* Distance to project plane from viewer (near) */
  VA6_RndProjFarClip;  /* Distance to project far clip plane (far) */
 
extern MATR
  VA6_RndMatrView, /* View coordinate system matrix */
  VA6_RndMatrProj, /* Projection coordinate system matrix */
  VA6_RndMatrVP;   /* Stored (View * Proj) matrix */

typedef struct tagva6VERTEX
{
  VEC P;  /* Vertex position */
  VEC4 C;
  VEC2 T;
  VEC N; 
} va6VERTEX;

typedef struct tagva6PRIM
{
  va6VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */
 
  INT *I;       /* Index array (for trimesh ñ by 3 ones) */
  INT NumOfI;   /* Number of indices */
 
  MATR Trans;   /* Additional transformation matrix */
} va6PRIM;
 

BOOL VA6_RndPrimCreate( va6PRIM *Pr, INT NoofV, INT NoofI );
VOID VA6_RndPrimFree( va6PRIM *Pr );
VOID VA6_RndPrimDraw( va6PRIM *Pr, MATR World );
BOOL VA6_RndPrimLoad( va6PRIM *Pr, CHAR *FileName );
BOOL VA6_RndPrimCreateSphere( va6PRIM *Pr, DBL R, INT W, INT H ); 
BOOL VA6_RndPrimCreate—ylinder( va6PRIM *Pr, DBL R, INT W, INT H );
/* BOOL VA6_RndPrimCreateThor( va6PRIM *Pr, DBL R, INT W, INT H ); */
BOOL VA6_RndPrimLoad( va6PRIM *Pr, CHAR *FileName );

VOID VA6_RndInit( HWND hWnd );
VOID VA6_RndClose( VOID );
VOID VA6_RndResize( INT W, INT H );
VOID VA6_RndCopyFrame( VOID );
VOID VA6_RndStart( VOID );
VOID VA6_RndEnd( VOID );
VOID VA6_RndProjSet( VOID );
VOID VA6_RndCamSet( VEC Loc, VEC At, VEC Up );