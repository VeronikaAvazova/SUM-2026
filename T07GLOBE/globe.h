/* FILE NAME  : globe.h
 * PROGRAMMER : VA6
 * LAST UPDATE: 06.06.2026
 */
#include "mth.h"
#include <windows.h>

typedef DOUBLE DBL;


#define PI 3.14159265358979323846
#define GLB_MIN(A, B) ((A) < (B) ? (A) : (B))
#define GLB_MAX(A, B) ((A) > (B) ? (A) : (B))

#define GLB_GRID_W 31
#define GLB_GRID_H 18

VOID GLB_Init( DBL R );
VOID GLB_Draw( HDC hDC );
VOID GLB_Resize( INT Ws, INT Hs );