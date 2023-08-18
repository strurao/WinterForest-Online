#include "pch.h"
#include "InputManager.h"

void InputManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_states.resize(KEY_TYPE_COUNT, KeyState::None); // 256
}

void InputManager::Update()
{
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	// ::GetAsyncKeyState() // 현재 키가 눌려있는지 체크하는 법이나, 매 프레임마다 하려면 좀 느리다
	if (::GetKeyboardState(asciiKeys) == false) // 키보드 256개의 상태를 통으로 하나로 긁어와서 저장하고 필요에 따라 체크하기
		return;

	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		// 키가 눌려있으면 true
		if (asciiKeys[key] & 0x80) // 비트플래그 체크
		{
			KeyState& state = _states[key];

			// 이전 프레임에 키를 누른 상태라면 PRESS
			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::Press;
			else
				state = KeyState::Down;
		}
		// 키보드에서 손을 놓았을때
		else
		{
			KeyState& state = _states[key];

			// 이전 프레임에 키를 누른 상태라면 UP
			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::Up;
			else
				state = KeyState::None;
		}
	}

	//Mouse
	::GetCursorPos(&_mousePos); // 마우스의 현재 좌표를 알아온다
	::ScreenToClient(_hwnd, &_mousePos); // 창 기준 마우스 포인트
}
