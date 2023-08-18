#pragma once
#include "UI.h"

class Sprite;

enum ButtonState
{
	BS_Default,
	// BS_Hovered,
	BS_Pressed,
	BS_Clicked,

	BS_MaxCount
};

class Button : public UI
{
	using Super = UI;

public:
	Button();
	virtual ~Button() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void SetSize(Vec2Int size) { _size = size; }
	Sprite* GetSprite(ButtonState state) { return _sprites[state]; }

	void SetCurrentSprite(Sprite* sprite) { _currentSprite = sprite; }
	void SetSprite(Sprite* sprite, ButtonState state) { _sprites[state] = sprite; }
	void SetButtonState(ButtonState state);

	// void OnClickButton() {}

protected:
	Sprite* _currentSprite = nullptr;
	Sprite* _sprites[BS_MaxCount] = {};
	ButtonState _state = BS_Default;

	float _sumTime = 0.f;

public:
	template<typename T>
	void AddOnClickDelegate(T* owner, void(T::* func)())
	{
		_onClick = [owner, func]()
		{
			(owner->*func)();
		};
	}

	// 함수 포인터 + 함수 객체
	std::function<void(void)> _onClick = nullptr;

	/*
	// 함수 포인터 예
	static void Test() {}
	// void(*_onClickFunc)();
	using OnClickButtonFuncType = void(*)();
	OnClickButtonFuncType _onClickFunc = nullptr;
	void TestMem() {}
	using OnClickButtonMemFuncType = void(Button::*)();
	Button* _owner = nullptr;
	OnClickButtonMemFuncType _onClickMemFunc = nullptr;
	*/

};

