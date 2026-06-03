/* Avazova Veronika, 10-6, 03.06.2009 */
#include <windows.h>
#include <math.h>
#define WND_CLASS_NAME "039"
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                    CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;

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
  
  CreateWindowA(WND_CLASS_NAME, "minions", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    100, 100, 900, 900, NULL, NULL, hInstance, NULL);

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  HDC hDC;
  HPEN hPen, hOldPen;
  RECT rc;
  static BITMAP bm;
  static HBITMAP hBm;
  SYSTEMTIME st;
  PAINTSTRUCT ps;
  CHAR Buf[100];
  static INT W, H;
  static HBITMAP hBmClockface;
  static HDC hMemDCClockface, hMemDC;
  
  switch (Msg)
  {  

  case WM_ERASEBKGND:
    return 0;
  
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);

    GetLocalTime(&st);

    MoveToEx(hMemDC, W / 2 - W / 51, H / 2 + H / 27, NULL);
    LineTo(hMemDC, (INT)(W / 2 - W / 51 + sin((st.wSecond + st.wMilliseconds / 1000.0) / 60.0 * 2 * 3.14) * W / 2.5), (INT)(H / 2 + H / 27 - cos((st.wSecond + st.wMilliseconds / 1000.0) / 60.0 * 2 * 3.14) * H / 2.5));

    hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    hOldPen = SelectObject(hMemDC, hPen);
    MoveToEx(hMemDC, W / 2 - W / 51, H / 2 + H / 27, NULL);
    LineTo(hMemDC, (INT)(W / 2 - W / 51 + sin((st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0) / 60.0 * 2 * 3.14) * W / 3.5), (INT)(H / 2 + H / 27 - cos((st.wMinute + st.wSecond / 60.0 + st.wMilliseconds / 60000.0)  / 60.0 * 2 * 3.14) * H / 3.5));
    SelectObject(hMemDC, hOldPen);
    DeleteObject(hPen);

    hPen = CreatePen(PS_SOLID, 9, RGB(0, 0, 0));
    hOldPen = SelectObject(hMemDC, hPen);
    MoveToEx(hMemDC, W / 2 - W / 51, H / 2 + H / 27, NULL);
    LineTo(hMemDC, (INT)(W / 2 - W / 51 + sin((st.wHour + st.wMinute / 60.0 + st.wSecond / 360.0) / 12.0 * 2 * 3.14) * W / 5), (INT)(H / 2 + H / 27 - cos((st.wHour + st.wMinute / 60.0 + st.wSecond / 360.0) / 12.0 * 2 * 3.14) * H / 5));
    SelectObject(hMemDC, hOldPen);
    DeleteObject(hPen);
    
    rc.bottom = H;
    rc.left = 0;
    rc.right = W;
    rc.top = 0;
    wsprintf(Buf, "%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);
    SetBkMode(hMemDC, TRANSPARENT);
    DrawText(hMemDC, Buf, wsprintf(Buf, "%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond), &rc, DT_CENTER);
    /*TextOut(hMemDC, 130, 30, Buf, wsprintf(Buf, "%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond)); */
    
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    
    EndPaint(hWnd, &ps);
    return 0;

  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);

    if (hBm != NULL)
      DeleteObject(hBm);

    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);

    ReleaseDC(hWnd, hDC);
    return 0;

  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    hMemDCClockface = CreateCompatibleDC(hDC);
    hBmClockface = LoadImage(NULL, "Capture.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    GetObject(hBmClockface, sizeof(bm), &bm);

    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 3, 8, NULL);
    return 0;

  case WM_TIMER:
    SelectObject(hMemDC, hBm);
    
    SelectObject(hMemDCClockface, hBmClockface);
    BitBlt(hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, hMemDCClockface, 0, 0, SRCCOPY);
    SetStretchBltMode(hMemDC, COLORONCOLOR);
    StretchBlt(hMemDC, 0, 0, W, H, hMemDCClockface, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
    
    InvalidateRect(hWnd, NULL, TRUE);
    break;

  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 30);
    PostMessage(NULL, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}