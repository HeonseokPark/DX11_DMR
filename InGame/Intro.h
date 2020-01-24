#pragma once
#include "GameNode.h"
class Intro : public GameNode
{
public:
	Intro();
	~Intro() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

