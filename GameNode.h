#pragma once
#include "stdafx.h"
class GameNode
{

public:
	//S_OK
	//성공적으로 호출 된 경우
	
	//E_FAIL
	//함수를 호출하는 중에 에러가 생길 경우
	//순수 가상함수로 노드 작성
	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update()  = 0;
	virtual void render()  = 0;
	GameNode() {};
	virtual ~GameNode() {};
};

