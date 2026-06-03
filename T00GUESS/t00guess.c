/* Avazova Veronika, 10-6, 01.06.2026 */
#include <windows.h>
#include <stdio.h>

void main( void )
{
  int a = 0, b = 100, m, res;
  char s[100];
  
  MessageBox(NULL, "Загадай число от 0 до 100", "Guess", MB_YESNOCANCEL);
  while (b >= a)
  {
    m = (a + b) / 2;
    sprintf(s, "Число больше %i?", m);
    res = MessageBox(NULL, s, "Guess", MB_YESNOCANCEL);
    if (res == IDYES)
      a = m + 1;
    else
      if (res == IDNO)
        b = m - 1;
      else
      {
        sprintf(s, "Ваше число %i?", m);
        MessageBox(NULL, s, "Guess", MB_OK);
        break;
      }
  }
}