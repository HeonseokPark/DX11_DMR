#pragma once
#include "SingletonBase.h"

class ImageManager :public SingletonBase<ImageManager>
{
private:
	typedef map<string, Image*>				ImgMap;//������ ���� �̹��� ���
	typedef map<string, Image*>::iterator	ImgIter;//������ ���� �̹��� ����� �ݺ���

	ImgMap m_ImgMap;
	Rect* rect;
	Circle* circle;
public:
	
	Image* AddImage(string strKey, _tstring file, string ps = "PS");
	Image* AddImage(string strKey, _tstring file, UINT MaxFrameX, UINT MaxFrameY, string ps = "PS");

	//�̹��� Ű������ ã��
	Image* GetImage(string strkey);
	//�̹��� Ű������ ����
	bool DeleteImage(string strKey);
	//���� ����
	void DeleteAll();
	//�Ϲݷ���
	void Render(string strKey);
	//���� ����
	void LoofRender(string strKey,float x = 0.0f,float y=0.0f);

	//�ִϸ��̼�
	void PlayAnimation(string strKey,PlayState ps, bool isFrameX, float nexttime);

	//Rect�� Circle�� IMAGEMANAGER �� �ϳ��� ����ִ�.
	void RectRender() { rect->Render(); }
	void CircleRender() { circle->Render(); }

	MAKEGET(Rect*, rect);
	MAKEGET(Circle*, circle);

	ImageManager() { rect = new Rect(); circle = new Circle(72); };
	~ImageManager() { SAFE_DELETE(rect) SAFE_DELETE(circle) };
};

