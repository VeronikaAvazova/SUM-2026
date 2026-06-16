/* FILE NAME  : rndres.h
 * PROGRAMMER : VA6
 * LAST UPDATE: 13.06.2026
 */

#ifndef __rndres_h_
#define __rndres_h_

#include "def.h"


VOID VA6_RndResInit( VOID );
VOID VA6_RndResClose( VOID );

#define VA6_STR_MAX 300

/* Shader program store type */
typedef struct tagva6SHADER
{
  CHAR Name[VA6_STR_MAX]; /* Shader filename prefix */
  UINT ProgId;            /* Shader program Id */
} va6SHADER;
 
/* Shaders stock maximum size */
#define VA6_MAX_SHADERS 30
 
/* Array of shaders */
extern va6SHADER VA6_RndShaders[VA6_MAX_SHADERS];
/* Shadres array store size */
extern INT VA6_RndShadersSize;

INT VA6_RndShdAdd( CHAR *ShaderFileNamePrefix );
VOID VA6_RndShdUpdate( VOID );
VOID VA6_RndShdInit( VOID );
VOID VA6_RndShdClose( VOID );

#endif /* __rndres_h_ */