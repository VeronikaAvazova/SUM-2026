/* FILE NAME  : timer.h
 * PROGRAMMER : VA6
 * LAST UPDATE: 09.06.2026
 */
 
#ifndef __timer_h_
#define __timer_h_

extern DOUBLE GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
  GLB_Time, GLB_DeltaTime,             /* Time with pause and interframe interval */
  GLB_FPS;                         /* Frames per second value */
extern BOOL
  GLB_IsPause;                     /* Pause flag */


VOID GLB_TimerInit( VOID );
VOID GLB_TimerResponse( VOID );

#endif /* __timer_h_ */
 
/* END OF 'timer.h' FILE */