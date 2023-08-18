#pragma once
#include <Windows.h>
#include <string>
using namespace std;

class Utils
{
public:
	static void DrawText(HDC hdc, Pos pos, const wstring& str);

	static void DrawRect(HDC hdc, Pos pos, int32 w, int32 h);

	static void DrawCircle(HDC hdc, Pos pos, int32 radius);

	static void DrawLine(HDC hdc, Pos from, Pos to);

	static void DrawLineColored(HDC hdc, Pos from, Pos to, COLORREF color);

	static void ReadBmp(const wstring& path);
};
