#pragma once
#include "GameNode.h"

class OptionMenu : public GameNode
{

	// �ɼ� �߰��� ��
	// 1. Ǯ��ũ�� & â���
	// 2. ���� ũ��

private:
	bool _isFullScreen;
	
	float _Volume;
	
public:
	OptionMenu();
	~OptionMenu()override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

