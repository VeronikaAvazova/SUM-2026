/* FILE NAME: t00check.c
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: VA6
 * DATE: 08.06.2026
 */
#include <stdio.h>
#include "mth.h"

void main( void )
{
  FILE *F;
  VEC r;

  F = fopen("CHECK.TXT", "a");
  if (F == NULL)
    return;

  r = VecAddVec({1, 1, 1}, {2, 3, 0});
  fprintf(F, "%f, %f, %f", r.X, r.Y, r.Z );

  fclose(F);
}