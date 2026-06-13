/* FILE NAME  : timer.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 09.06.2026
 */
#include "anim.h"

typedef unsigned long long UINT64;

DOUBLE GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
  Time, DeltaTime,             /* Time with pause and interframe interval */
  FPS;                         /* Frames per second value */
BOOL
  IsPause;                     /* Pause flag */

static UINT64
  StartTime,    /* Start program time */
  OldTime,      /* Previous frame time */
  OldTimeFPS,   /* Old time FPS measurement */
  PauseTime,    /* Time during pause period */
  TimePerSec,   /* Timer resolution */
  FrameCounter; /* Frames counter */

VOID VA6_TimerInit( VOID )
{
  LARGE_INTEGER t;
 
  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);

  StartTime = t.QuadPart;

  FrameCounter = 0;
  VA6_Anim.IsPause = FALSE;
  VA6_Anim.FPS = 30.0;
  VA6_Anim.Time = VA6_Anim.DeltaTime = 0;
  PauseTime = 0;
} 

VOID VA6_TimerResponse( VOID )
{
  LARGE_INTEGER t;
 
  QueryPerformanceCounter(&t);
 
  /* Global time */
  VA6_Anim.GlobalTime = (DOUBLE)(t.QuadPart - StartTime) / TimePerSec;
  VA6_Anim.GlobalDeltaTime = (DOUBLE)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (VA6_Anim.IsPause)
  {
    VA6_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    VA6_Anim.DeltaTime = VA6_Anim.GlobalDeltaTime;
    VA6_Anim.Time = (DOUBLE)(t.QuadPart - PauseTime - StartTime) / TimePerSec; 
  }
 
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    VA6_Anim.FPS = FrameCounter * TimePerSec / (DOUBLE)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
}