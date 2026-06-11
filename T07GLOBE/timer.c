/* FILE NAME  : timer.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 09.06.2026
 */
#include <time.h>
#include <windows.h>
#include "timer.h"

typedef unsigned long long UINT64;

DOUBLE GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
  GLB_Time, GLB_DeltaTime,             /* Time with pause and interframe interval */
  GLB_FPS;                         /* Frames per second value */
BOOL
  GLB_IsPause;                     /* Pause flag */

static UINT64
  StartTime,    /* Start program time */
  OldTime,      /* Previous frame time */
  OldTimeFPS,   /* Old time FPS measurement */
  PauseTime,    /* Time during pause period */
  TimePerSec,   /* Timer resolution */
  FrameCounter; /* Frames counter */

VOID GLB_TimerInit( VOID )
{
  LARGE_INTEGER t;
 
  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  GLB_IsPause = FALSE;
  GLB_FPS = 30;
  PauseTime = 0;
  /*GLB_Time = GLB_DeltaTime = 0;   */
} 

VOID GLB_TimerResponse( VOID )
{
  LARGE_INTEGER t;
 
  QueryPerformanceCounter(&t);
 
  /* Global time */
  GlobalTime = (DOUBLE)(t.QuadPart - StartTime) / TimePerSec;
  GlobalDeltaTime = (DOUBLE)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (GLB_IsPause)
  {
    GLB_DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    GLB_DeltaTime = GlobalDeltaTime;
    GLB_Time = (DOUBLE)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
 
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    GLB_FPS = FrameCounter * TimePerSec / (DOUBLE)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
}