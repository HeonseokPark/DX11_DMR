#pragma once
#include "SingletonBase.h"

class KeyManager :public SingletonBase<KeyManager>
{
private:
	bool KeyDown[256];
	BYTE prevKey;
	//0~ 255


public:
	KeyManager();
	~KeyManager();
	//�������� Ȯ��
	bool isKeyDown(int KeyCode);
	//��� ������ �ִ���
	bool StayKeyDown(int KeyCode);
	//��ư�� ��������
	bool isKeyUp(int KeyCode);
	//�ѹ� ������ ���
	bool ToggleKeyDown(int KeyCode);

};

