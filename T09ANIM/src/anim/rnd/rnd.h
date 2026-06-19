/* FILE NAME: rnd.h
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: VA6
 * DATE: 09.06.2026
 */

#define GLEW_STATIC
#include "opengl/glew.h"

#include "res/rndres.h"

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

VOID VA6_RndInit( HWND hWnd );
VOID VA6_RndClose( VOID );
VOID VA6_RndResize( INT W, INT H );
VOID VA6_RndCopyFrame( VOID );
VOID VA6_RndStart( VOID );
VOID VA6_RndEnd( VOID );
VOID VA6_RndProjSet( VOID );
VOID VA6_RndCamSet( VEC Loc, VEC At, VEC Up );


extern VEC VA6_RndCamLoc, VA6_RndCamAt, VA6_RndCamRight, VA6_RndCamUp, VA6_RndCamDir; 

typedef struct tagva6VERTEX
 {
  VEC P;   /* позици€ */
  VEC2 T;  /* текстурна€ координата */
  VEC N;   /* нормаль */
  VEC4 C;  /* ÷вет (r,g,b,a) */
} va6VERTEX;

/* Primitive type */
typedef enum tagva6PRIM_TYPE
{
  VA6_RND_PRIM_POINTS,   /* Array of points  Ц GL_POINTS */
  VA6_RND_PRIM_LINES,    /* Line segments (by 2 points) Ц GL_LINES */
  VA6_RND_PRIM_TRIMESH,  /* Triangle mesh - array of triangles Ц GL_TRIANGLES */
  VA6_RND_PRIM_TRISTRIP,
} va6PRIM_TYPE;

/* Primitive representation type */
typedef struct tagva6PRIM
{
  va6PRIM_TYPE Type; /* Primitive type */
 
  INT
    VA,              /* Vertex array Id */
    VBuf,            /* Vertex buffer Id */
    IBuf;            /* Index buffer Id (if 0 - use only vertex buffer) */
 
  INT NumOfElements; /* Number of indices/vecrtices */
 
  VEC MinBB, MaxBB;  /* Bound box */
 
  MATR Trans;   /* Additional transformation matrix */
  INT MtlNo; /* Material number at stock array */
  INT ShdNo;
} va6PRIM;

/* Grid topology representation type */
typedef struct tagva6GRID
{
  INT W, H;      /* Grid size (in vertices) */
  va6VERTEX *V;  /* Array (2D) of vertex */
} va6GRID;


VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
                             INT Length, const CHAR *Message,
                             const VOID *UserParam );
 

VOID VA6_RndPrimCreate( va6PRIM *Pr, va6PRIM_TYPE Type,
                        va6VERTEX *V, INT NoofV, INT *Ind, INT NoofI );
VOID VA6_RndPrimFree( va6PRIM *Pr );
VOID VA6_RndPrimDraw( va6PRIM *Pr, MATR World );
BOOL VA6_RndPrimLoad( va6PRIM *Pr, CHAR *FileName );
BOOL VA6_RndPrimCreateSphere( va6PRIM *Pr, DBL R, INT W, INT H ); 
BOOL VA6_RndPrimCreate—ylinder( va6PRIM *Pr, DBL R, INT W, INT H );
/* BOOL VA6_RndPrimCreateThor( va6PRIM *Pr, DBL R, INT W, INT H ); */
BOOL VA6_RndPrimLoad( va6PRIM *Pr, CHAR *FileName );
VOID VA6_RndPrimTriMeshAutoNormals( va6VERTEX *V, INT NumOfV, INT *Ind, INT NumOfI);


BOOL VA6_RndGridCreate( va6GRID *G, INT W, INT H );
VOID VA6_RndGridFree( va6GRID *G ); 
VOID VA6_RndPrimFromGrid( va6PRIM *Pr, va6GRID *G );
VOID VA6_RndGridAutoNormals( va6GRID *G );
BOOL VA6_RndGridCreateSphere( va6GRID *G, FLT R, INT W, INT H );
