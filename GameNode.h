#pragma once
#include "stdafx.h"
class GameNode
{

public:
	//S_OK
	//���������� ȣ�� �� ���
	
	//E_FAIL
	//�Լ��� ȣ���ϴ� �߿� ������ ���� ���
	//���� �����Լ��� ��� �ۼ�
	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update()  = 0;
	virtual void render()  = 0;
	GameNode() {};
	virtual ~GameNode() {};
};

