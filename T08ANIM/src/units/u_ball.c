/* FILE NAME  : u_ball.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 11.06.2026
 */

#include "anim/anim.h"
#include "units.h"

typedef struct 
{
  UNIT_BASE_FIELDS;
  VEC Pos;
} va6UNIT_BALL;

static VOID VA6_UnitInit( va6UNIT_BALL *Uni, va6ANIM *Ani )
{
  Uni->Pos = VecSet(0, 1, 0);
}

static VOID VA6_UnitResponse( va6UNIT_BALL *Uni, va6ANIM *Ani )
{
  Uni->Pos += Ani->DeltaTime * 2.4;
}

static VOID VA6_UnitRender( va6UNIT_BALL *Uni, va6ANIM *Ani )
{
  DrawSphere(Uni->Pos, 3);
}

va6UNIT * VA6_UnitCreateBall( VOID )
{
  va6UNIT_BALL *Uni;
 
  Uni = AnimUnitCreate(sizeof(UNIT_COW));
  if ((Uni = (va6UNIT_BALL *)VA6_AnimUnitCreate(sizeof(va6UNIT_BALL) == NULL)
    return NULL;
  Uni->Init = (VOID *)VA6_UnitInit;
  Uni->Responce = (VOID *)VA6_UnitResponce;
  Uni->Render = (VOID *)VA6_UnitRender;
  return (va6UNIT *)Uni;
}