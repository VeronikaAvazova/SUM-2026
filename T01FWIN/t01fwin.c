/* Avazova Veronika, 10-6, 01.06.2009 */
#include <windows.h>
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
  
  CreateWindowA(WND_CLASS_NAME, "eyes", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    1000, 100, 500, 400, NULL, NULL, hInstance, NULL);

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
  PAINTSTRUCT ps;
  static INT W, H;
  
  switch (Msg)
  {  
  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);

    Ellipse(hDC, 0, 0, W / 2, H);
    Ellipse(hDC, W / 2, 0, W, H);
    SelectObject(hDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hDC, RGB(50, 30, 10));
    SelectObject(hDC, GetStockObject(DC_PEN));
    SetDCPenColor(hDC, RGB(0, 0, 0));  
    Ellipse(hDC, W / 6, H / 6, W / 2, H - (H / 6));
    Ellipse(hDC, W / 2 + W / 6, H / 6, W, H - (H / 6));
    SelectObject(hDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hDC, RGB(0, 0, 0));
    Ellipse(hDC, W / 3, H / 3, W / 2, H - (H / 3));
    Ellipse(hDC, W / 2 + W / 3, H / 3, W, H - (H / 3));

    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    PostMessage(NULL, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}