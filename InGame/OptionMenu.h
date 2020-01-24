#pragma once
#include "GameNode.h"

class OptionMenu : public GameNode
{

	// 옵션 추가할 거
	// 1. 풀스크린 & 창모드
	// 2. 음악 크기
public:
	OptionMenu();
	~OptionMenu()override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

