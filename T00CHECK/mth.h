/* FILE NAME: mth.h
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: VA6
 * DATE: 08.06.2026
 */
 
#ifndef __mth_h_
#define __mth_h_
 
#include <math.h>
 
//#include <windows.h>   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 
/* Pi math constant */
#define PI 3.14159265358979323846
 
/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
 
 
/* Base float point types */
typedef double DBL;
typedef float FLT;
 
/* Space vector/point representation type */
typedef struct tagVEC
{
  DBL X, Y, Z; /* Vector coordinates */
} VEC;
 
/* Transformation matrix representation type */
typedef struct tagMATR
{
  DBL A[4][4]; /* Matrix elements */
} MATR;
 
__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC r = {X, Y, Z};
 
  return r;
}

/* Add two vectors function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */

__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */
 
/* Vector by matrix multiplication (with homogenious devide) function.
 * ARGUMENTS:
 *   - source vector:
 *       VEC V;
 *   - multiplied matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMulMatr( VEC V, MATR M )
{
  DBL w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];
 
  return VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w,
                (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w,
                (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w);
} /* End of 'VecMulMatr' function */
 
#endif /* __mth_h_ */
 
/* END OF 'mth.h' FILE */