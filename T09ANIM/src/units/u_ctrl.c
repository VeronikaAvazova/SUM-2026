/* FILE NAME  : u_ctrl.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 11.06.2026
 */

#include "stdio.h"
#include "units.h"

typedef struct tagva6UNIT_CONTROL
{
  VA6_UNIT_BASE_FIELDS;
  VEC CamLoc, CamAt;
  DBL Speed;
} va6UNIT_CONTROL;

static VOID VA6_UnitInit( va6UNIT_CONTROL *Uni, va6ANIM *Ani )
{
  Uni->CamLoc = VecSet(8, 8, 8);
  Uni->CamAt = VecSet(0, 0, 0);
  Uni->Speed = 10;
}

static VOID VA6_UnitClose( va6UNIT_CONTROL *Uni, va6ANIM *Ani )
{
}

static VOID VA6_UnitResponse( va6UNIT_CONTROL *Uni, va6ANIM *Ani )
{
  VEC d;

  /*if (Ani->Keys[VK_CONTROL] && Ani->KeysClick['F'])
    VG4_AnimFlipFullScreen(); */
 
  if (Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;

  if (Ani->KeysClick[VK_ESCAPE])
    VA6_AnimDoExit();

  d = VecNormalize(VecSubVec(Uni->CamAt, Uni->CamLoc));

  Uni->CamLoc =
    VecAddVec(Uni->CamLoc,
      VecMulNum(d, Ani->GlobalDeltaTime * Uni->Speed *
        (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN])));

  VA6_RndCamSet(Uni->CamLoc, Uni->CamAt, VecSet(0, 1, 0));
} 

static VOID VA6_UnitRender( va6UNIT_CONTROL *Uni, va6ANIM *Ani )
{
  /*CHAR Buf[102];
  
  SetBkMode(Ani->hDC, TRANSPARENT);
  SetTextColor(Ani->hDC, RGB(255, 255, 0));
  TextOut(Ani->hDC, Ani->W - 200, 30, Buf, sprintf(Buf, "FPS: %.3f", Ani->FPS));
*/}

va6UNIT * VA6_UnitCreateControl( VOID )
{
  va6UNIT *Uni;
 
  if ((Uni = VA6_AnimUnitCreate(sizeof(va6UNIT_CONTROL))) == NULL)
    return NULL;

  Uni->Init = (VOID *)VA6_UnitInit;
  Uni->Close = (VOID *)VA6_UnitClose;
  Uni->Response = (VOID *)VA6_UnitResponse;
  Uni->Render = (VOID *)VA6_UnitRender;
  return Uni;
}