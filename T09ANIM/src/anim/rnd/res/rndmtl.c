/* FILE NAME  : rndmtl.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 17.06.2026
 */

#include "anim/rnd/rnd.h"

/* Array of materials */
va6MATERIAL VA6_RndMaterials[VA6_MAX_MATERIALS]; 
/* Materials array store size */
INT VA6_RndMaterialsSize;


va6MATERIAL VA6_RndMtlGetDef( VOID )
{
  va6MATERIAL def_mtl =
  {
    "Default",
    {0.1, 0.1, 0.1},
    {0.90, 0.90, 0.90},
    {0.30, 0.30, 0.30},
    30, 1,
    {-1, -1, -1, -1, -1, -1, -1, -1},
    0
  };

  return def_mtl;
}

VOID VA6_RndMtlInit( VOID )
{
  va6MATERIAL def = VA6_RndMtlGetDef();

  VA6_RndMaterialsSize = 0;
  VA6_RndMtlAdd(&def);
}


VOID VA6_RndMtlClose( VOID )
{
}


INT VA6_RndMtlAdd( va6MATERIAL *Mtl )
{
  if (VA6_RndMaterialsSize >= VA6_MAX_MATERIALS)
    return 0;
  VA6_RndMaterials[VA6_RndMaterialsSize] = *Mtl;
  return VA6_RndMaterialsSize++;
}

UINT VA6_RndMtlApply( INT MtlNo )
{
  UINT prg;
  va6MATERIAL *mtl;
  INT loc, i;
 
  /* Set material pointer */
  if (MtlNo < 0 || MtlNo >= VA6_RndMaterialsSize)
    MtlNo = 0;
  mtl = &VA6_RndMaterials[MtlNo];
 
  /* Set shader program Id */
  prg = mtl->ShdNo;
  if (prg < 0 || (INT)prg >= VA6_RndShadersSize)
    prg = VA6_RndShaders[0].ProgId;
  else
    prg = VA6_RndShaders[prg].ProgId;
 
  if (prg == 0)
    return 0;
 
  glUseProgram(prg);
 
  /* Set shading parameters */
  if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);
  if ((loc = glGetUniformLocation(prg, "Trans")) != -1)
    glUniform1f(loc, mtl->Trans);
 
  /* Set textures */
  for (i = 0; i < 8; i++)
  {
    CHAR tname[] = "IsTexture0";
    CHAR tnamew[] = "Texture0W";
    CHAR tnameh[] = "Texture0H";
	BOOL IsTex = FALSE;

    tname[9] = '0' + i;
	tnamew[7] = '0' + i;    
	tnameh[7] = '0' + i;
    
	if (mtl->Tex[i] != -1 && mtl->Tex[i] >= 0 && mtl->Tex[i] < VA6_RndTexturesSize)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, VA6_RndTextures[mtl->Tex[i]].TexId);
    }
    if ((loc = glGetUniformLocation(prg, tname)) != -1)
      glUniform1i(loc, mtl->Tex[i] != -1);
  }
  return prg;
}