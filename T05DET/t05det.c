/* Avazova Veronika, 10-6, 04.06.2026 */
#include <stdio.h>
#include <windows.h>

#define N 10
typedef DOUBLE DBL;

INT a[N];
DBL A[N][N];
INT M;
DBL Det = 0;

VOID Swap( INT i, INT j)
{
  INT buf;          

  buf = a[i];
  a[i] = a[j];
  a[j] = buf;
}

BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;
 
  M = 0;
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;
  fscanf(F, "%d", &M);

  if (M > N)
    M = N;
  else
    if (M < 0)
      M = 0;

  for (i = 0; i < M; i++)
    for (j = 0; j < M; j++)
      fscanf(F, "%lf", &A[i][j]);

  fclose(F);
  return TRUE;
}

VOID Go( INT i, INT IsP)
{
  INT k, l;
  DBL prod;
  
  if (i == M)
  {
    for (prod = 1, l = 0; l < M; l++)
      prod *= A[l][a[l]];
    Det += prod * (IsP ? 1 : -1);
  }
  else
  {
    for (k = i; k < M; k++)
    {
      Swap(k, i);
      if (i != k)
        IsP = ! IsP;
      Go(i + 1, IsP);
      Swap(k, i);
      if (i != k)
        IsP = ! IsP;
    }
  }
}

void main( void )
{
  INT i, IsP = 1;
  DBL prod;

  LoadMatrix("DET.TXT");
  
  for (prod = 1, i = 0; i < M; i++)
    a[i] = i;

  Go(0, IsP);
  printf("%f ", Det);
  getchar();
}