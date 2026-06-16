/* FILE NAME  : u_ball.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 11.06.2026
 */

#include "units.h"

typedef struct tagva6UNIT_BALL
{
  VA6_UNIT_BASE_FIELDS;
  VEC Pos;
  va6PRIM Ball;
} va6UNIT_BALL;

static VOID VA6_UnitInit( va6UNIT_BALL *Uni, va6ANIM *Ani )
{
  VA6_RndPrimCreateSphere(&Uni->Ball, 0.1, 30, 12);
  Uni->Pos = VecSet(Rnd1() * 4, 1, Rnd1() * 4);
}

static VOID VA6_UnitClose( va6UNIT_BALL *Uni, va6ANIM *Ani )
{
  VA6_RndPrimFree(&Uni->Ball); 
}

static VOID VA6_UnitResponse( va6UNIT_BALL *Uni, va6ANIM *Ani )
{
} 

static VOID VA6_UnitRender( va6UNIT_BALL *Uni, va6ANIM *Ani )
{
  VA6_RndPrimDraw(&Uni->Ball, MatrTranslate(VecAddVec(Uni->Pos, VecSet(0, fabs(sin(5 * Ani->Time)), 0))));
}

va6UNIT * VA6_AnimUnitCreateBall( VOID )
{
  va6UNIT_BALL *Uni;
 
  if ((Uni = (va6UNIT_BALL *)VA6_AnimUnitCreate(sizeof(va6UNIT_BALL))) == NULL)
    return NULL;

  Uni->Init = (VOID *)VA6_UnitInit;
  Uni->Response = (VOID *)VA6_UnitResponse;
  Uni->Render = (VOID *)VA6_UnitRender;
  return (va6UNIT *)Uni;
}