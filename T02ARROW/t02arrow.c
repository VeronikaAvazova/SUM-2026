/* Avazova Veronika, 10-6, 02.06.2009 */
#include <windows.h>
#include <math.h>
#define WND_CLASS_NAME "039"
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

void DrawArrow( HWND hWnd, HDC hDC, INT x, INT y, INT l)
{
  POINT pt, pts[3] = {{10, 0}, {-10, 0}, {0, 10}},
            pts_res[sizeof(pts) / sizeof(pts[0])];
  INT i, xk, yk;
  DOUBLE c, s;

  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);
    
  xk = (int)((pt.x - x) * l / sqrt((pt.x - x) * (pt.x - x) + (pt.y - y) * (pt.y - y)) + x);
  yk = (int)((pt.y - y) * l / sqrt((pt.x - x) * (pt.x - x) + (pt.y - y) * (pt.y - y)) + y);
  c = (pt.y - y) / sqrt((pt.x - x) * (pt.x - x) + (pt.y - y) * (pt.y - y));
  s = (pt.x - x) / sqrt((pt.x - x) * (pt.x - x) + (pt.y - y) * (pt.y - y));

  for (i = 0; i < sizeof(pts) / sizeof(pts[0]); i++)
  {
    pts_res[i].x = (int)(xk + pts[i].x * c + pts[i].y * s);
    pts_res[i].y = (int)(yk + pts[i].y * c - pts[i].x * s);
  }
  
  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(0, 0, 0));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(0, 0, 200));  
    
  Polygon(hDC, pts_res, 3);


  MoveToEx(hDC, x, y, NULL);
  LineTo(hDC, xk, yk);
}

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                    CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  MSG msg;
  HWND hWnd;

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
  
  hWnd = CreateWindowA(WND_CLASS_NAME, "umbrella", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
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
  HBRUSH hBr, hOldBr;
  static HBITMAP hBm;
  static BITMAP bm;
  static BOOL is_select = FALSE;
  PAINTSTRUCT ps;
  static INT W, H;
  int i, j;
  static HDC hMemDC;

  switch (Msg)
  {  
  case WM_ERASEBKGND:
    return 0;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    
    hBr = CreateSolidBrush(RGB(255, 255, 255));
    hOldBr = SelectObject(hMemDC, hBr);
    Rectangle(hMemDC, 0, 0, W, H);
    SelectObject(hMemDC, hOldBr);
    DeleteObject(hBr);

    srand(30);
    for (i = 0; i < 30; i++)
      DrawArrow(hWnd, hMemDC, rand() % W, rand() % H, 20);
    /*for (i = 0; i < (H / 10); i++)
      for (j = 0; j < (W / 10); j++)
        DrawArrow(hWnd, hMemDC, H / 10 * i, W / 10 * j, 20);     */
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

    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 3, 8, NULL);
    return 0;

  case WM_TIMER:
    SelectObject(hMemDC, hBm);

    InvalidateRect(hWnd, NULL, TRUE);
    break;

  case WM_MOUSEMOVE:
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;

  case WM_CLOSE:
    if (MessageBox(hWnd, "Are you sure close window?", "Exit", MB_YESNO | MB_ICONQUESTION) == IDNO)
      return 0;
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