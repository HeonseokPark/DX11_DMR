#include "stdafx.h"
#include "ImageManager.h"


Image * ImageManager::AddImage(string strKey, _tstring file, string ps)
{
	Image* img = GetImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� ����
	if (img) return img;

	//�������� �ʴ´ٸ�
	img = new Image(file, ps);
	//������ �̹����� ������ ���� ��Ͽ� �߰��Ѵ�
	m_ImgMap.insert(make_pair(strKey, img));
	return img;
}

Image * ImageManager::AddImage(string strKey, _tstring file, UINT MaxFrameX, UINT MaxFrameY, string ps)
{
	Image* img = GetImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� ����
	if (img) return img;

	//�������� �ʴ´ٸ�
	img = new Image(file, MaxFrameX, MaxFrameY, ps);
	//������ �̹����� ������ ���� ��Ͽ� �߰��Ѵ�
	m_ImgMap.insert(make_pair(strKey, img));
	return img;
}

Image * ImageManager::GetImage(string strkey)
{
	//�ش� Ű������ Ž�� �ϴµ� Ű���� ������ �Ǹ������� end �� ��ȯ�ȴ�.
	ImgIter iter = m_ImgMap.find(strkey);

	//�˻��� Ű�� ã�Ҵٸ�
	if (iter != m_ImgMap.end())
	{
		return iter->second;
	}
	//��ã���� nullptr ��ȯ
	return nullptr;
}

bool ImageManager::DeleteImage(string strKey)
{
	//�ش� Ű�� �˻�
	ImgIter iter = m_ImgMap.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ�
	if (iter != m_ImgMap.end())
	{
		//�̹��� ����� ������ �� �����Ҵ� ����
		SAFE_DELETE(iter->second);
		//�ʿ��� �߰� ����
		m_ImgMap.erase(iter);
		return true;
	}
	return false;
}

void ImageManager::DeleteAll()
{
	ImgIter iter = m_ImgMap.begin();
	for (iter; iter != m_ImgMap.end();)
	{
		if (iter->second != nullptr)
		{
			SAFE_DELETE(iter->second);
			iter = m_ImgMap.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	m_ImgMap.clear();
}

void ImageManager::Render(string strKey)
{
	//�̹����� ã�� �� ����
	Image* img = GetImage(strKey);
	if (img) img->Render();
}

void ImageManager::LoofRender(string strKey, float x, float y)
{
	//�̹����� ã�� �� ����
	Image* img = GetImage(strKey);
	if (img) img->LoofRender(x,y);
}

void ImageManager::PlayAnimation(string strKey, PlayState ps, bool isFrameX, float nexttime)
{
	//�̹����� ã�� �� ����
	Image* img = GetImage(strKey);
	if (img) img->PlayAnimation(ps, isFrameX, nexttime);
}
