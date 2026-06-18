/* FILE NAME  : u_land.c
 * PROGRAMMER : VA6
 * LAST UPDATE: 15.06.2026
 */

#include "units.h"

typedef struct tagva6UNIT_LAND
{
  VA6_UNIT_BASE_FIELDS;
  va6PRIM Land;
} va6UNIT_LAND;

static VOID VA6_UnitInit( va6UNIT_LAND *Uni, va6ANIM *Ani )
{
  HBITMAP hBm;
  BITMAP bm;

  if ((hBm = LoadImage(NULL, "bin/heights/hfcolor.bmp", IMAGE_BITMAP, 0, 0,
                      LR_LOADFROMFILE | LR_CREATEDIBSECTION)) != NULL)
  {
    INT w, h;
    va6GRID G;

    GetObject(hBm, sizeof(bm), &bm);
    w = bm.bmWidth;
    h = bm.bmHeight;
    if (VA6_RndGridCreate(&G, w, h))
    {
      BYTE *Bits = bm.bmBits;
      INT x, y;
      FLT size = 1000;

      for (y = 0; y < h; y++)
      {
        for (x = 0; x < w; x++)
        {
          INT hgt = Bits[(h - 1 - y) * bm.bmWidthBytes + x * (bm.bmBitsPixel >> 3)];

          G.V[y * G.W + x].P = VecSet((2 * x / (w - 1.0) - 1) * size, 30 * hgt / 255.0, (1 - 2 * y / (h - 1.0)) * size);
        }
      }
      VA6_RndGridAutoNormals(&G);
      VA6_RndPrimFromGrid(&Uni->Land, &G);
      VA6_RndGridFree(&G);
    }
  }
}

static VOID VA6_UnitClose( va6UNIT_LAND *Uni, va6ANIM *Ani )
{
  VA6_RndPrimFree(&Uni->Land); 
}

static VOID VA6_UnitResponse( va6UNIT_LAND *Uni, va6ANIM *Ani )
{
} 

static VOID VA6_UnitRender( va6UNIT_LAND *Uni, va6ANIM *Ani )
{
  VA6_RndPrimDraw(&Uni->Land, MatrIdentity());
}

va6UNIT * VA6_AnimUnitCreateLand( VOID )
{
  va6UNIT *Uni;
 
  if ((Uni = VA6_AnimUnitCreate(sizeof(va6UNIT_LAND))) == NULL)
    return NULL;

  Uni->Init = (VOID *)VA6_UnitInit;
  Uni->Close = (VOID *)VA6_UnitClose; 
  Uni->Response = (VOID *)VA6_UnitResponse;
  Uni->Render = (VOID *)VA6_UnitRender;
  return Uni;
}