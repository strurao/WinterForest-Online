#include "pch.h"
#include "UI.h"
#include "InputManager.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::BeginPlay()
{
}

void UI::Tick()
{
}

void UI::Render(HDC hdc)
{
}

RECT UI::GetRect()
{
	RECT rect =
	{
		_pos.x - _size.x / 2, //LEFT
		_pos.y - _size.y / 2, //TOP
		_pos.x + _size.x / 2, //RIGHT
		_pos.y + _size.y / 2, //BOTTOM
	};

	return rect;
}

bool UI::IsMouseInRect()
{
	RECT rect = GetRect();
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	// return ::PtInRect(&rect, mousePos);
	if (mousePos.x < rect.left)
		return false;
	if (mousePos.x > rect.right)
		return false;
	if (mousePos.y < rect.top)
		return false;
	if (mousePos.y > rect.bottom)
		return false;

	return true;
}
