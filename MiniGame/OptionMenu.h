#pragma once
#include "GameNode.h"

class OptionMenu : public GameNode
{
public:
	OptionMenu();
	~OptionMenu()override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

