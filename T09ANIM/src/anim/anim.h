/* FILE NAME  : anim.h
 * PROGRAMMER : VA6
 * LAST UPDATE: 11.06.2026
 */

#ifndef __anim_h_
#define __anim_h_

#include "rnd/rnd.h"

#define VA6_MAX_UNITS 3000
 
typedef struct tagva6UNIT va6UNIT;
typedef struct tagva6ANIM va6ANIM;

#define VA6_UNIT_BASE_FIELDS \
  VOID (*Init)( va6UNIT *Uni, va6ANIM *Ani );      \
  VOID (*Close)( va6UNIT *Uni, va6ANIM *Ani );     \
  VOID (*Response)( va6UNIT *Uni, va6ANIM *Ani );  \
  VOID (*Render)( va6UNIT *Uni, va6ANIM *Ani )


struct tagva6UNIT
{
  VA6_UNIT_BASE_FIELDS;
};

struct tagva6ANIM
{
  HWND hWnd;                      
  HDC hDC;                        
  INT W, H;                    
 
 
  va6UNIT * Units[VA6_MAX_UNITS]; 
  INT NumOfUnits;            
 
  DBL
    GlobalTime, GlobalDeltaTime, 
    Time, DeltaTime,         
    FPS;                      
  BOOL
    IsPause;
};  

extern va6ANIM VA6_Anim;

VOID VA6_AnimInit( HWND hWnd );
VOID VA6_AnimClose( VOID );
VOID VA6_AnimResize( INT W, INT H );
VOID VA6_AnimCopyFrame( VOID );
VOID VA6_AnimRender( VOID );
VOID VA6_AnimAddUnit( va6UNIT *Uni );
VOID VA6_AnimFlipFullScreen( VOID );
VOID VA6_AnimExit( VOID );

VOID VA6_AnimUnitAdd( va6UNIT *Uni );
va6UNIT * VA6_AnimUnitCreate( INT Size );

VOID VA6_TimerInit( VOID );
VOID VA6_TimerResponse( VOID );

#endif /* __anim_h_ */