/* FILE NAME  : u_cow.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 15.06.2026
 */

#include "units.h"

typedef struct tagva6UNIT_COW
{
  VA6_UNIT_BASE_FIELDS;
  va6PRIM Cow;
} va6UNIT_COW;

static VOID VA6_UnitInit( va6UNIT_COW *Uni, va6ANIM *Ani )
{
  VA6_RndPrimLoad(&Uni->Cow, "bin/models/cow.obj");
}

static VOID VA6_UnitClose( va6UNIT_COW *Uni, va6ANIM *Ani )
{
  VA6_RndPrimFree(&Uni->Cow); 
}

static VOID VA6_UnitRender( va6UNIT_COW *Uni, va6ANIM *Ani )
{
  INT s = 0, i, j;

  for (i = -s; i <= s; i++)  
    for (j = -s; j <= s; j++)
      VA6_RndPrimDraw(&Uni->Cow, 
        MatrMulMatr5(MatrScale(VecSet1(0.1)),
        MatrRotateY(Ani->Time * 180),
        MatrRotateX(sin(Ani->Time) * 30), 
        MatrRotateZ(sin(Ani->Time) * 30),
        MatrTranslate(VecSet(1, j, i))));
}

va6UNIT * VA6_AnimUnitCreateCow( VOID )
{
  va6UNIT *Uni;
 
  if ((Uni = VA6_AnimUnitCreate(sizeof(va6UNIT_COW))) == NULL)
    return NULL;

  Uni->Init = (VOID *)VA6_UnitInit;
  Uni->Close = (VOID *)VA6_UnitClose;
  Uni->Render = (VOID *)VA6_UnitRender;
  return Uni;
}