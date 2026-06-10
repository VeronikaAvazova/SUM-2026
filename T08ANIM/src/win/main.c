/* FILE NAME  : main.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 09.06.2026
 */
#include <windows.h>
#include <time.h>
#include "def.h"
#include "anim/rnd/rnd.h"

/* Window class name */
#define WND_CLASS_NAME "039"

/* Forward declaration */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

/* Main startup program function.
 * ARGUMENTS:
 *   - application instance handle:
 *       HINSTANCE hInstance;
 *   - previouse application instance handle
 *     (not used, alway NULL):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - command line window show parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) system error level value.
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                    CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;
  HWND hWnd;

  SetDbgMemHooks();

  /* Window class register */
  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error", "ERROR", MB_ICONERROR | MB_OK);
    return 0;
  }
  
  /* Create window */
  hWnd = CreateWindowA(WND_CLASS_NAME, "anim", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    100, 100, 700, 700, NULL, NULL, hInstance, NULL);

  /* Message loop */
  while (TRUE)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
      SendMessage(hWnd, WM_TIMER, 47, 0);
  return msg.wParam;
} /* End of 'WinMain' function */

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  HDC hDC;
  PAINTSTRUCT ps;
  static INT W, H;
  static va6PRIM Pr, Pr1, Pr2, Pr3;
  
  switch (Msg)
  {  

  case WM_ERASEBKGND:
    return 1;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    VA6_RndCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    VA6_RndResize(W, H);
    SendMessage(hWnd, WM_TIMER, 47, 0);

    return 0;

  case WM_CREATE:
    VA6_RndInit(hWnd);
    
    SetTimer(hWnd, 3, 8, NULL);
    if (VA6_RndPrimCreate(&Pr, 4, 6))
    {
      Pr.V[0].P = VecSet(0, 0, 0);
      Pr.V[1].P = VecSet(2, 0, 0);
      Pr.V[2].P = VecSet(0, 2, 0);
      Pr.V[3].P = VecSet(2, 2, 0);
 
      Pr.I[0] = 0;
      Pr.I[1] = 1;
      Pr.I[2] = 2;
 
      Pr.I[3] = 2;
      Pr.I[4] = 1;
      Pr.I[5] = 3;
    }
    
    VA6_RndPrimCreateSphere(&Pr1, 1, 8, 5);
    VA6_RndPrimCreate—ylinder(&Pr2, 3, 30, 4);
    /* VA6_RndPrimCreateThor(&Pr3, 3, 20, 20);    */

    return 0;

  case WM_TIMER:
    VA6_RndStart();
   
    hDC = GetDC(hWnd);
    
   /* SelectObject(VA6_hRndDCFrame, GetStockObject(DC_PEN));
    SetDCPenColor(VA6_hRndDCFrame, RGB(168, 228, 160));
    VA6_RndPrimDraw(&Pr, MatrRotateY(30.0 * clock() / 1000.0));   */

    SelectObject(VA6_hRndDCFrame, GetStockObject(DC_PEN));
    SetDCPenColor(VA6_hRndDCFrame, RGB(255, 117, 20));
    Pr1.Trans = MatrTranslate(VecSet(2, 1, 0));
    /* VA6_RndPrimDraw(&Pr1, MatrTranslate(VecSet(0, fabs(sin(3 * clock() / 1000.0)), 0)));  */

    SelectObject(VA6_hRndDCFrame, GetStockObject(DC_PEN));
    SetDCPenColor(VA6_hRndDCFrame, RGB(168, 228, 160));
    /* Pr2.Trans = MatrTranslate(VecSet(2, 1, 0));
    VA6_RndPrimDraw(&Pr2, MatrRotateY(30.0 * clock() / 1000.0)); */

    /* Pr3.Trans = MatrTranslate(VecSet(2, 1, 0));
    VA6_RndPrimDraw(&Pr3, MatrRotateY(30.0 * clock() / 1000.0));  */
    VA6_RndPrimLoad(&Pr3, "bin/models/cow.obj");
    Pr3.Trans = MatrMulMatr(MatrScale(VecSet1(1.1)), MatrTranslate(VecSet(-2, 2, 0)));
    VA6_RndPrimDraw(&Pr3, MatrTranslate(VecSet(0, fabs(sin(3 * clock() / 1000.0)), 0)));



    VA6_RndEnd();
    VA6_RndCopyFrame(hDC);
    ReleaseDC(hWnd, hDC);
    return 0;

  case WM_DESTROY:
    VA6_RndPrimFree(&Pr);
    VA6_RndPrimFree(&Pr1);
    VA6_RndPrimFree(&Pr2);
    /* VA6_RndPrimFree(&Pr3);   */ 
    VA6_RndClose();
    KillTimer(hWnd, 30);
    PostMessage(NULL, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}/* End of 'MyWindowFunc' function */
    
/* END OF 'main.c' FILE */