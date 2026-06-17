/* FILE NAME  : rndres.h
 * PROGRAMMER : VA6
 * LAST UPDATE: 13.06.2026
 */

#ifndef __rndres_h_
#define __rndres_h_

#include "def.h"


VOID VA6_RndResInit( VOID );
VOID VA6_RndResClose( VOID );

#define VA6_STR_MAX 3000

/* Shaders stock maximum size */
#define VA6_MAX_SHADERS 30
/* Shader program store type */
typedef struct tagva6SHADER
{
  CHAR Name[VA6_STR_MAX]; /* Shader filename prefix */      
  UINT ProgId;            /* Shader program Id */
} va6SHADER;
/* Array of shaders */
extern va6SHADER VA6_RndShaders[VA6_MAX_SHADERS];
/* Shadres array store size */
extern INT VA6_RndShadersSize;

/* Textures stock maximum size */
#define VA6_MAX_TEXTURES 300
/* Textures program store type */
typedef struct tagva6TEXTURES
{
  CHAR Name[VA6_STR_MAX]; /* Texture name */
  INT W, H;               /* Texture size in pixels */
  UINT TexId;             /* OpenGL texture Id */  
} va6TEXTURES;
/* Array of textures */
extern va6TEXTURES VA6_RndTextures[VA6_MAX_TEXTURES];
/* Textures array store size */
extern INT VA6_RndTexturesSize;  

/* Materials program store type */
typedef struct tagva6MATERIAL
{
  CHAR Name[VA6_STR_MAX]; /* Material name */
 
  /* Illumination coefficients */    
  VEC Ka, Kd, Ks;           /* Ambient, diffuse, specular coefficients */
  FLT Ph;                   /* Phong power coefficient */
 
  FLT Trans;                /* Transparency factor */
 
  INT Tex[8];               /* Texture references from texture table (or -1) */
 
  INT ShdNo;                /* Shader number in shader table */ 
} va6MATERIAL;
/* Materials stock maximum size */
#define VA6_MAX_MATERIALS 300
/* Array of materials */
extern va6MATERIAL VA6_RndMaterials[VA6_MAX_MATERIALS]; 
/* Materials array store size */
extern INT VA6_RndMaterialsSize;



 
INT VA6_RndShdAdd( CHAR *ShaderFileNamePrefix );
VOID VA6_RndShdUpdate( VOID );
VOID VA6_RndShdInit( VOID );
VOID VA6_RndShdClose( VOID );

VOID VA6_RndTexInit( VOID );
VOID VA6_RndTexClose( VOID );
INT VA6_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits );
INT VA6_RndTexAdd( CHAR *FileName );

va6MATERIAL VA6_RndMtlGetDef( VOID );
VOID VA6_RndMtlInit( VOID ); 
VOID VA6_RndMtlClose( VOID );
INT VA6_RndMtlAdd( va6MATERIAL *Mtl );
UINT VA6_RndMtlApply( INT MtlNo );

#endif /* __rndres_h_ */