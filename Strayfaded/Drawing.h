#pragma once
#include "include.h"

void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR col);
void DrawLine(int x1, int y1, int x2, int y2, int thickness, bool antialias, D3DCOLOR col);
void DrawBoundingBox(int baseX, int baseY, int width, int height, int thickness, bool antialias, D3DCOLOR color);
void DrawCorneredBox(int baseX, int baseY, int width, int height, int thickness, float coverage, bool antialias, D3DCOLOR color);

void DrawMessage(LPD3DXFONT font, unsigned int x, unsigned int y, int alptha, unsigned char r, unsigned char g, unsigned char b, LPCSTR Message);
void DrawHealthText(LPD3DXFONT font, unsigned int x, unsigned int y, int health, int armor);

void DrawHealthbar2(int baseX, int baseY, int width, int headPos, bool antialias, int EntityHealth);
void DrawHealthBar(int baseX, int baseY, int width, int height, int thickness, bool antialias, int EntityHealth, int EntityArmor);