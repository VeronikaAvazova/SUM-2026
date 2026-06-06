/* FILE NAME  : globe.h
 * PROGRAMMER : VA6
 * LAST UPDATE: 06.06.2026
 */
#include <windows.h>

typedef DOUBLE DBL;

typedef struct
{
  DBL X, Y, Z;
} VEC;

#define PI 3.14159265358979323846
#define GLB_MIN(A, B) ((A) < (B) ? (A) : (B))
#define GLB_MAX(A, B) ((A) > (B) ? (A) : (B))

#define GLB_GRID_W 31
#define GLB_GRID_H 18

static DBL GLB_Ws, GLB_Hs;
static DBL GLB_Wp, GLB_Hp, GLB_ProjSize = 1;

static VEC GLB_Geom[GLB_GRID_H][GLB_GRID_W];
static VEC GLB_GeomN[GLB_GRID_H][GLB_GRID_W];

VOID GLB_Init( DBL R );
VOID GLB_Draw( HDC hDC );
VOID GLB_Resize( INT Ws, INT Hs );