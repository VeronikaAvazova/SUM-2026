/* Avazova Veronika, 10-6, 04.06.2026 */
#include <stdio.h>
#include <windows.h>

#define N 4
INT a[N];

VOID Swap( INT i, INT j)
{
  INT buf;

  buf = a[i];
  a[i] = a[j];
  a[j] = buf;
}

VOID Go( INT i, INT IsP )
{
  INT k;
  FILE *F;

  F = fopen("PERM.TXT", "a");
  if (F == NULL)
    return;

  if (i == N)
  {
    for (k = 0; k < N; k++)
      fprintf(F, "%i ", a[k]);
    fprintf(F, IsP ? " even\n" : " odd\n");
  }
  else
  {
    for (k = i; k < N; k++)
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
  fclose(F);
}

void main( void )
{
  INT i, IsP = 1;

  for (i = 0; i < N; i++)
    a[i] = i + 1;

  Go(0, IsP);
}