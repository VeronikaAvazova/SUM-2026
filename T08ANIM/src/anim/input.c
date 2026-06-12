/* FILE NAME  : input.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 12.06.2026
 */

#include "anim.h"

static BYTE OldKeys[256];

static VOID KeyboardInit( VOID )
{
  INT i;

  GetKeyboardState(VA6_Anim.Keys);
  for (i = 0; i < 256; i++)
    VA6_Anim.Keys[i] >>= 7;
  memcpy(OldKeys, VA6_Anim.Keys, 256);
}

static VOID Keyboar  ( VOID )
{
