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
	Image* Option;		//옵션 버튼 이미지
	Image* storyMode;	//이야기 상태 이미지
	Image* infiniteMode; //무한 상태 이미지

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

