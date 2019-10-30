#pragma once


#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

HRESULT InitD3D(HWND hWnd);
void Boxer_Finalize();
void Boxer_Update();
void Boxer_Draw();

void TextDraw(LPD3DXFONT pFont, char* text, int X, int Y);