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
	//�ɼ� �޴� �߰��ؾ��� ����
	//1. BGM �� ȿ���� ON/OFF �� ���� ����
	//2. ��üȭ�� / â��� ����

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
