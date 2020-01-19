#include "stdafx.h"
#include "MainMenu.h"


MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

HRESULT MainMenu::init()
{
	m_isGameStart = false;
	m_Option = false;
	
	m_LogoY = -500.0f;
	optionCC = CircleMake(50.0f, 50.0f, 50.0f); //�ɼ� ��ư

	//SOUNDMANAGER->addSound
	BackGround = IMGMANAGER->GetImage("Main");
	Logo = IMGMANAGER->GetImage("Logo");
	Option = IMGMANAGER->GetImage("Option");
	SOUNDMANAGER->play("BGM", 1.0f);
	return S_OK;
}

void MainMenu::release()
{
}

void MainMenu::update()
{
	if (m_LogoY <= 450.0f)
	{
		m_LogoY += 100.0f * g_ETime;
	}
	
	if (KEYMANAGER->isKeyDown(VK_LBUTTON))
	{
		//m_Option = true;
	}
	if (PtInCircle(optionCC, g_ptMouse))
	{
		//Option->PlayAnimation("PS2", 1, 2);
	}
}

void MainMenu::render()
{
	if (m_isGameStart == false)
	{
		BackGround->Scale(WINSIZEX, WINSIZEY);
		BackGround->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
		BackGround->Rotate(0.0f, 0.0f, 0.0f);
		BackGround->Render();

		Logo->Scale(700.0f, 400.0f);
		Logo->Position(WINSIZEX / 2.0f, m_LogoY);
		Logo->Rotate(0.0f, 0.0f, 0.0f);
		Logo->Render();
	}
	if (m_Option == false)
	{
		Option->Position(50.0f, 50.0f);
		Option->Scale(50.0f, 50.0f);
		Option->Rotate(0.0f, 0.0f, 0.0f);
		Option->Render();
	}
}