/* FILE NAME  : t07globe.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 06.06.2026
 */
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "globe.h"
#include "timer.h"
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
  hWnd = CreateWindowA(WND_CLASS_NAME, "globe", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
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
  static BITMAP bm;
  static HBITMAP hBm;
  PAINTSTRUCT ps;
  static INT W, H;
  static HBITMAP hBmClockface;
  static HDC hMemDCClockface, hMemDC;
  CHAR Buf[100];
  
  switch (Msg)
  {  

  case WM_CREATE:
    SetTimer(hWnd, 3, 8, NULL);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    hBm = NULL;

    GLB_TimerInit();
    GLB_Init(0.3);
    return 0;

  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    GLB_Resize(W, H);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    return 0;

  case WM_ERASEBKGND:
    return 0;

  case WM_KEYDOWN:
    if (wParam == 'P')
      GLB_IsPause = !GLB_IsPause;
    return 0;
  
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);

    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    
    EndPaint(hWnd, &ps);
    return 0;


  case WM_TIMER:
    GLB_TimerResponse();
    if (W > 0 && H > 0)
    {
      SelectObject(hMemDC, hBm);
    
      SelectObject(hMemDC, GetStockObject(DC_BRUSH));
      SelectObject(hMemDC, GetStockObject(DC_PEN));

      SetDCPenColor(hMemDC, RGB(0, 0, 0));
      SetDCBrushColor(hMemDC, RGB(0, 0, 0));
      Rectangle(hMemDC, 0, 0, W, H);

      GLB_Draw(hMemDC);

      SetBkMode(hMemDC, TRANSPARENT);
      SetTextColor(hMemDC, RGB(55, 255, 255));
      TextOut(hMemDC, 30, 30, Buf, sprintf(Buf, "FPS: %.2f", GLB_FPS));

      hDC = GetDC(hWnd);
      ReleaseDC(hWnd, hDC);
      InvalidateRect(hWnd, NULL, TRUE);
    }
    break;

  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 30);
    PostMessage(NULL, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}/* End of 'MyWindowFunc' function */
    
/* END OF 't07globe.c' FILE */