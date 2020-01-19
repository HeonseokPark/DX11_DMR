#pragma once
#include "SingletonBase.h"

//Ŭ����(����ü) ���漱��
struct FontBrushDesc;
struct FontTextDesc;

class WriteManager : public SingletonBase<WriteManager>
{
private:
	//dx11���� �ؽ�Ʈ�� ����Ҽ� ���� ������ d2d�� dxwrite�� �ҷ��ͼ� ����ؾ� ��.

	//d2d�� dxwrite �� �İ�ü��
	ID2D1Factory1 * factory;//Direct2D ���ҽ��� ����� ����
	IDWriteFactory* writeFactory = NULL;//DirectWrite ��ü�� ����� �� ���

	ID2D1Device* device;//d2d ����̽�
	ID2D1DeviceContext* deviceContext = NULL;//d2d ����̽����ؽ�Ʈ

	ID2D1Bitmap1* targetBitmap; //�׷��� ��Ʈ��. ID3D11Texture2D ���� �����̶� ���� ��
	vector<FontBrushDesc> fontBrush; //��Ʈ �귯�� ����
	vector<FontTextDesc> fontText; //��Ʈ �ؽ�Ʈ ����
public:
	void RenderText
	(
		wstring text
		, RECT rect
		, float size = 20.0f
		, wstring font = L"����ü"
		, D3DXCOLOR color = D3DXCOLOR(1, 1, 1, 1)
		, DWRITE_FONT_WEIGHT weight = DWRITE_FONT_WEIGHT_NORMAL
		, DWRITE_FONT_STYLE style = DWRITE_FONT_STYLE_NORMAL
		, DWRITE_FONT_STRETCH stretch = DWRITE_FONT_STRETCH_NORMAL
	);

public:
	WriteManager();
	~WriteManager();
	ID2D1DeviceContext* GetDc() { return deviceContext; }
};


struct FontBrushDesc
{
	D3DXCOLOR Color;
	ID2D1SolidColorBrush* Brush = NULL;//HBRUSH ����� ��
	//���� ���� �ִ��� Ȯ���ϱ� ���� ������ �����ε�
	bool operator==(const FontBrushDesc& val)
	{
		return Color.r == val.Color.r &&
			Color.g == val.Color.g &&
			Color.b == val.Color.b &&
			Color.a == val.Color.a;
	}
};

struct FontTextDesc
{
	wstring Font;
	float FontSize;

	DWRITE_FONT_WEIGHT Weight;
	DWRITE_FONT_STYLE Style;
	DWRITE_FONT_STRETCH Stretch;

	IDWriteTextFormat* Format = NULL;//HFONT ����� ��
	//���� ���� �ִ��� Ȯ���ϱ� ���� ������ �����ε�
	bool operator==(const FontTextDesc& val)
	{
		bool b = true;
		b &= Font == val.Font;
		b &= FontSize == val.FontSize;
		b &= Weight == val.Weight;
		b &= Style == val.Style;
		b &= Stretch == val.Stretch;

		return b;
	}
};