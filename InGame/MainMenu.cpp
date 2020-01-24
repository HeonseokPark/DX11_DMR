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
	optionCC = CircleMake(50.0f, 50.0f, 50.0f); //옵션 버튼

	//SOUNDMANAGER->addSound
	BackGround = IMGMANAGER->GetImage("Main");
	Logo = IMGMANAGER->GetImage("Logo");
	Option = IMGMANAGER->GetImage("Option");
	storyMode = IMGMANAGER->GetImage("storyMode");
	infiniteMode = IMGMANAGER->GetImage("infinityMode");
	SOUNDMANAGER->play("BGM", 1.0f);

	optionTouch = false;
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
	
	if (optionTouch == true && KEYMANAGER->isKeyDown(VK_LBUTTON))
	{
		m_Option = true;
	}
	if (PtInCircle(optionCC, g_ptMouse))
	{
		optionTouch = true;
		Option->PlayAnimation(ANI_LOOP, 1, 1);
	}
	else
	{
		optionTouch = false;
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

		if (m_LogoY >= 450.0f)
		{
			storyMode->Scale(263.0f, 58.0f);
			storyMode->Position(640.0f, m_LogoY - 300.0f);
			storyMode->Rotate(0.0f, 0.0f, 0.0f);
			storyMode->Render();

			infiniteMode->Scale(263.0f, 58.0f);
			infiniteMode->Position(640.0f, m_LogoY - 360.0f);
			infiniteMode->Rotate(0.0f, 0.0f, 0.0f);
			infiniteMode->Render();
		}

	}
	if (m_Option == false)
	{
		Option->Position(50.0f, 50.0f);
		Option->Scale(50.0f, 50.0f);
		Option->Rotate(0.0f, 0.0f, 0.0f);
		Option->Render();
	}
}
