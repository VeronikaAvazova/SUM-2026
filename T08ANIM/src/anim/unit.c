/* FILE NAME  : unit.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 11.06.2026
 */

#include "anim.h"
/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       va6UNIT *Uni;
 *   - animation context:
 *       va6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VA6_UnitInit( va6UNIT *Uni, va6ANIM *Ani )
{
} /* End of 'VA6_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       va6UNIT *Uni;
 *   - animation context:
 *       va6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VA6_UnitClose( va6UNIT *Uni, va6ANIM *Ani )
{
} /* End of 'VA6_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       va6UNIT *Uni;
 *   - animation context:
 *       va6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VA6_UnitResponse( va6UNIT *Uni, va6ANIM *Ani )
{
} /* End of 'VA6_UnitResponse' function */
 
/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       va6UNIT *Uni;
 *   - animation context:
 *       va6ANIM *Ani;
 * RETURNS: None.
 */
static VOID VA6_UnitRender( va6UNIT *Uni, va6ANIM *Ani )
{
} /* End of 'VA6_UnitRender' function */
 
/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (va6UNIT *) pointer to created unit.
 */
va6UNIT * VA6_AnimUnitCreate( INT Size )
{
  va6UNIT *Uni;
 
  /* Memory allocation */
  if (Size < sizeof(va6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
 
  /* Setup unit methods */
  Uni->Init = VA6_UnitInit;
  Uni->Close = VA6_UnitClose;
  Uni->Response = VA6_UnitResponse;
  Uni->Render = VA6_UnitRender;
 
  return Uni;
} /* End of 'VA6_AnimUnitCreate' function */