/* FILE NAME  : rndbase.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 09.06.2026
 */

#include "rnd.h"

#include "wglew.h"
#include "gl/wglext.h"

#pragma comment(lib, "opengl32")


VOID VA6_RndInit( HWND hWnd )
{
  INT i, nums;
  PIXELFORMATDESCRIPTOR pfd = {0};
  HGLRC hRC;
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                                  /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB, */
    0
  };

  
  VA6_hRndWnd = hWnd;

  /* Prepare frame compatible device contesxt */
  VA6_hRndDC = GetDC(hWnd);
 
  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(VA6_hRndDC, &pfd);
 
  DescribePixelFormat(VA6_hRndDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(VA6_hRndDC, i, &pfd);
 
  /* OpenGL init: rendering context setup */
  VA6_hRndGLRC = wglCreateContext(VA6_hRndDC);
  wglMakeCurrent(VA6_hRndDC, VA6_hRndGLRC);

  if (glewInit() != GLEW_OK)
    exit(0);
 
  /* Render parameters setup */
  glEnable(GL_DEPTH_TEST);
 
  VA6_RndProjSize = 0.1;
  VA6_RndProjDist = VA6_RndProjSize;
  VA6_RndProjFarClip = 300;
  VA6_RndFrameW = 47;
  VA6_RndFrameH = 47;
  VA6_RndCamSet(VecSet(5, 5, 5), VecSet(0, 0, 0), VecSet(0, 1, 0));

  /* Enable a new OpenGL profile support */
  wglChoosePixelFormatARB(VA6_hRndDC, PixelAttribs, NULL, 1, &i, &nums);
  hRC = wglCreateContextAttribsARB(VA6_hRndDC, NULL, ContextAttribs);
 
  if (hRC != NULL)
  {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(VA6_hRndGLRC);
 
    VA6_hRndGLRC = hRC;
    wglMakeCurrent(VA6_hRndDC, VA6_hRndGLRC);
  }
}

VOID VA6_RndClose( VOID )
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(VA6_hRndGLRC);
  ReleaseDC(VA6_hRndWnd, VA6_hRndDC);
}

VOID VA6_RndResize( INT W, INT H )
{
  glViewport(0, 0, W, H);
 
  /* Setup projection */
  VA6_RndFrameW = W;
  VA6_RndFrameH = H;
  VA6_RndProjSet();
}

VOID VA6_RndCopyFrame( VOID )
{
  SwapBuffers(VA6_hRndDC);
}


VOID VA6_RndStart( VOID )
{
  VEC4 ClearColor = {0.30, 0.47, 0.8, 1};
  FLT DepthClearValue = 1;
 
  /* Clear frame */
  glClearBufferfv(GL_COLOR, 0, &ClearColor.X);
  glClearBufferfv(GL_DEPTH, 0, &DepthClearValue);
}

VOID VA6_RndEnd( VOID )
{
  glFinish();
}

VOID VA6_RndProjSet( VOID )
{
  DBL rx, ry;
 
  rx = ry = VA6_RndProjSize;
  /* Correct aspect ratio */
  if (VA6_RndFrameW > VA6_RndFrameH)
    rx *= (DBL)VA6_RndFrameW / VA6_RndFrameH;
  else
    ry *= (DBL)VA6_RndFrameH / VA6_RndFrameW;
  VA6_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      VA6_RndProjDist, VA6_RndProjFarClip);
  VA6_RndMatrVP = MatrMulMatr(VA6_RndMatrView, VA6_RndMatrProj);
}
  
VOID VA6_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  VA6_RndMatrView = MatrView(Loc, At, Up);
  VA6_RndMatrVP = MatrMulMatr(VA6_RndMatrView, VA6_RndMatrProj);
}