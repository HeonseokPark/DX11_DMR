#pragma once
#include "GameNode.h"
class MainMenu : public GameNode
{
private:
	bool m_isGameStart;
	bool m_Option;

public:
	Image* BackGround;	//백그라운드 배경 이미지
	Image* Logo;		//로고 이미지
	Image* Option;
	float m_LogoY;
	FCIRCLE optionCC;
	bool optionTouch;


public:
	MainMenu();
	~MainMenu() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

