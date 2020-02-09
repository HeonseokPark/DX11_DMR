#include "stdafx.h"
#include "OptionMenu.h"


OptionMenu::OptionMenu()
{
}


OptionMenu::~OptionMenu()
{
}

HRESULT OptionMenu::init()
{
	//옵션 메뉴 추가해야할 사항
	//1. BGM 및 효과음 ON/OFF 및 음향 조절
	//2. 전체화면 / 창모드 설정

	_isFullScreen = false;
	_Volume = 1.0f;
	
	return S_OK;
}

void OptionMenu::release()
{
}

void OptionMenu::update()
{
}

void OptionMenu::render()
{
}
