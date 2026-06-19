/* FILE NAME  : u_tex.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 11.06.2026
 */

#include "units.h"

typedef struct tagva6UNIT_TEX
{
  VA6_UNIT_BASE_FIELDS;
  va6PRIM Pr;
  INT MtlNo, TexId;
} va6UNIT_TEX;

static VOID VA6_UnitInit( va6UNIT_TEX *Uni, va6ANIM *Ani )
{
  va6VERTEX V[] =
  {
    {{0, 0, 0}, {0, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{1, 0, 0}, {1, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{0, 1, 0}, {0, 1}, {0, 0, 1}, {1, 1, 1, 1}},
    {{1, 1, 0}, {1, 1}, {0, 0, 1}, {1, 1, 1, 1}},
  };
  FLT t[2][2] =
  {
    {0.8, 1},
    {1, 0.3}
  };
  va6MATERIAL mtl = VA6_RndMtlGetDef();
  
  strncpy(mtl.Name, "Texture sample", VA6_STR_MAX - 1);
  mtl.ShdNo = VA6_RndShdAdd("tex");
  Uni->MtlNo = VA6_RndMtlAdd(&mtl);

  glGenTextures(1, &Uni->TexId);
  glBindTexture(GL_TEXTURE_2D, Uni->TexId);
  glTexImage2D(GL_TEXTURE_2D, 0, 1, 2, 2, 0, GL_LUMINANCE, GL_FLOAT, t);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  VA6_RndPrimCreate(&Uni->Pr, VA6_RND_PRIM_TRISTRIP, V, 4, NULL, 0);
  /*Uni->Pr.MtlNo = Uni->MtlNo;*/

}

static VOID VA6_UnitClose( va6UNIT_TEX *Uni, va6ANIM *Ani )
{
  glDeleteTextures(1, &Uni->TexId);
  VA6_RndPrimFree(&Uni->Pr); 
}

static VOID VA6_UnitResponse( va6UNIT_TEX *Uni, va6ANIM *Ani )
{
} 

static VOID VA6_UnitRender( va6UNIT_TEX *Uni, va6ANIM *Ani )
{
  glActiveTexture(GL_TEXTURE0 + 5);
  glBindTexture(GL_TEXTURE_2D, Uni->TexId);
  VA6_RndPrimDraw(&Uni->Pr, MatrIdentity());
}

va6UNIT * VA6_AnimUnitCreateTexture( VOID )
{
  va6UNIT_TEX *Uni;
 
  if ((Uni = (va6UNIT_TEX *)VA6_AnimUnitCreate(sizeof(va6UNIT_TEX))) == NULL)
    return NULL;

  Uni->Init = (VOID *)VA6_UnitInit;
  Uni->Close = (VOID *)VA6_UnitClose;
  Uni->Response = (VOID *)VA6_UnitResponse;
  Uni->Render = (VOID *)VA6_UnitRender;
  return (va6UNIT *)Uni;
}