/* FILE NAME: mth.h
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: VA6
 * DATE: 09.06.2026
 */
 
#ifndef __mth_h_
#define __mth_h_
 
#include <math.h>
 
#include <windows.h>
 
/* Pi math constant */
#define PI 3.14159265358979323846
 
/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)
 
#define UnitMatrix \
{                  \
  {                \
    {1, 0, 0, 0},  \
    {0, 1, 0, 0},  \
    {0, 0, 1, 0},  \
    {0, 0, 0, 1}   \
  }                \
}

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
 
/* Add two vectors function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */

__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC r = {X, Y, Z};
 
  return r;
}

__inline VEC VecSet1( DBL A )
{
  VEC r = {A, A, A};
 
  return r;
}

/* преобразования */
__inline MATR MatrTranslate( VEC D )
{
  MATR r =
  {
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {D.X, D.Y, D.Z, 1},
    }
  };
 
  return r;
}

__inline MATR MatrScale( VEC S )
{
  MATR r =
  {
    {
      {S.X, 0, 0, 0},
      {0, S.Y, 0, 0},
      {0, 0, S.Z, 0},
      {0, 0, 0, 1},
    }
  };
 
  return r;
}

__inline MATR MatrRotateZ( DBL a )
{
  MATR r =
  {
    {
      {cos(D2R(a)), sin(D2R(a)), 0, 0},
      {-sin(D2R(a)), cos(D2R(a)), 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1},
    }
  };
 
  return r;
}

__inline MATR MatrRotateX( DBL a )
{
  MATR r =
  {
    {
      {1, 0, 0, 0},
      {0, cos(D2R(a)), sin(D2R(a)), 0},
      {0, -sin(D2R(a)), cos(D2R(a)), 0},
      {0, 0, 0, 1},
    }
  };
 
  return r;
}

__inline MATR MatrRotateY( DBL a )
{
  MATR r =
  {
    {
      {cos(D2R(a)), 0, -sin(D2R(a)), 0},
      {0, 1, 0, 0},
      {sin(D2R(a)), 0, cos(D2R(a)), 0},
      {0, 0, 0, 1},
    }
  };
 
  return r;
}

/* действия с векторами */
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */


__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
}

__inline VEC VecMulNum( VEC V1, DBL N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
}

__inline VEC VecDivNum( VEC V1, DBL N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
}

__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
}

/* скалярное произведение векторов */
__inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
}

/* векторное произведение векторов */
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  VEC r = {V1.Y * V2.Z - V1.Z * V2.Y,
           V1.Z * V2.X - V1.X * V2.Z,
           V1.X * V2.Y - V1.Y * V2.X};
  return r;
}

/* длина вектора */
__inline DBL VecLen( VEC V )
{
  DBL len = VecDotVec(V, V);
 
  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
}

__inline DBL VecLen2( VEC V )
{
  DBL len = VecDotVec(V, V);
 
  if (len == 1 || len == 0)
    return len;
  return len;
}

/* V / |V| */
__inline VEC VecNormalize( VEC V )
{
  DBL len = VecDotVec(V, V);
 
  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrt(len));
}

/*   V * M3x3   */
__inline VEC VectorTransform( VEC V, MATR M )
{
  return
    VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0],
           V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1],
           V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]);
}

/*   (V, 1) * M4x3   */
__inline VEC PointTransform( VEC V, MATR M )
{
  return
    VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0],
           V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1],
           V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]);
}

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

/* единичная матрица */
__inline MATR MatrIdentity( VOID )
{
  MATR I = UnitMatrix;
 
  return I;
}

__inline MATR MatrSet( DBL A00, DBL A01, DBL A02, DBL A03,
                       DBL A10, DBL A11, DBL A12, DBL A13,
                       DBL A20, DBL A21, DBL A22, DBL A23,
                       DBL A30, DBL A31, DBL A32, DBL A33 )
{
  MATR m =
  {
    {
      {A00, A01, A02, A03},
      {A10, A11, A12, A13},
      {A20, A21, A22, A23},
      {A30, A31, A32, A33},
    }
  };
 
  return m;
}

__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR r = {{{0}}};
  INT i, j, k;
 
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (k = 0; k < 4; k++)
        r.A[i][j] += M1.A[i][k] * M2.A[k][j];
  return r;
}

__inline DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                            DBL A21, DBL A22, DBL A23,
                            DBL A31, DBL A32, DBL A33 )
{
  return (A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 - 
          A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31);
}

__inline DBL MatrDeterm( MATR M )
{
  return
    M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                              M.A[2][1], M.A[2][2], M.A[2][3],
                              M.A[3][1], M.A[3][2], M.A[3][3]) +
    -M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                               M.A[2][0], M.A[2][2], M.A[2][3],
                               M.A[3][0], M.A[3][2], M.A[3][3]) +
    M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                              M.A[2][0], M.A[2][1], M.A[2][3],
                              M.A[3][0], M.A[3][1], M.A[3][3]) +
    -M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                               M.A[2][0], M.A[2][1], M.A[2][2],
                               M.A[3][0], M.A[3][1], M.A[3][2]);
}

__inline MATR MatrInverse( MATR M )
{
  DBL det = MatrDeterm(M);
  MATR r;
 
  if (det == 0)
    return MatrIdentity();
 
 
  /* Build adjoint matrix */
  r.A[0][0] =
    MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                  M.A[2][1], M.A[2][2], M.A[2][3],
                  M.A[3][1], M.A[3][2], M.A[3][3]) / det;
  r.A[1][0] =
    -MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[2][0], M.A[2][2], M.A[2][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]) / det;
  r.A[2][0] =
    MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                  M.A[2][0], M.A[2][1], M.A[2][3],
                  M.A[3][0], M.A[3][1], M.A[3][3]) / det;
  r.A[3][0] =
    -MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[2][0], M.A[2][1], M.A[2][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]) / det;
 
  r.A[0][1] =
    -MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                   M.A[2][1], M.A[2][2], M.A[2][3],
                   M.A[3][1], M.A[3][2], M.A[3][3]) / det;
  r.A[1][1] =
    MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                  M.A[2][0], M.A[2][2], M.A[2][3],
                  M.A[3][0], M.A[3][2], M.A[3][3]) / det;
  r.A[2][1] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                   M.A[2][0], M.A[2][1], M.A[2][3],
                   M.A[3][0], M.A[3][1], M.A[3][3]) / det;
  r.A[3][1] =
    MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                  M.A[2][0], M.A[2][1], M.A[2][2],
                  M.A[3][0], M.A[3][1], M.A[3][2]) / det;
 
  r.A[0][2] =
    MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                  M.A[1][1], M.A[1][2], M.A[1][3],
                  M.A[3][1], M.A[3][2], M.A[3][3]) / det;
  r.A[1][2] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]) / det;
  r.A[2][2] =
    MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                  M.A[1][0], M.A[1][1], M.A[1][3],
                  M.A[3][0], M.A[3][1], M.A[3][3]) / det;
  r.A[3][2] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]) / det;
 
  r.A[0][3] =
    -MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                   M.A[1][1], M.A[1][2], M.A[1][3],
                   M.A[2][1], M.A[2][2], M.A[2][3]) / det;
  r.A[1][3] =
    MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                  M.A[1][0], M.A[1][2], M.A[1][3],
                  M.A[2][0], M.A[2][2], M.A[2][3]) / det;
  r.A[2][3] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                   M.A[1][0], M.A[1][1], M.A[1][3],
                   M.A[2][0], M.A[2][1], M.A[2][3]) / det;
  r.A[3][3] =
    MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                  M.A[1][0], M.A[1][1], M.A[1][2],
                  M.A[2][0], M.A[2][1], M.A[2][2]) / det;
 
  return r;
}

__inline MATR MatrRotate( VEC P, DBL a )
{
  DBL c = cos(a), s = sin(a);
  MATR m;

  P = VecNormalize(P);
  m.A[0][0] = c + P.X * P.X * (1 - c);
  m.A[0][1] = P.X * P.Y * (1 - c) + P.Z * s;
  m.A[0][2] = P.X * P.Z * (1 - c) - P.Y * s;
  m.A[1][0] = P.Y * P.X * (1 - c) - P.Z * s;
  m.A[1][1] = c + P.Y * P.Y * (1 - c);
  m.A[1][2] = P.Y * P.Z * (1 - c) + P.X * s;
  m.A[2][0] = P.Z * P.X * (1 - c) + P.Y * s;
  m.A[2][1] = P.Z * P.Y * (1 - c) - P.X * s;
  m.A[2][2] = c + P.Z * P.Z * (1 - c);
  m.A[0][3] = 0;
  m.A[1][3] = 0;
  m.A[2][3] = 0;
  m.A[3][3] = 0;
  m.A[3][0] = 0;
  m.A[3][1] = 0;
  m.A[3][2] = 0;

  return m;
}

#endif /* __mth_h_ */
 
/* END OF 'mth.h' FILE */