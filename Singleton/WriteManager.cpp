#include "stdafx.h"
#include "WriteManager.h"


void WriteManager::RenderText(wstring text, RECT rect, float size, wstring font, D3DXCOLOR color, DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style, DWRITE_FONT_STRETCH stretch)
{
	FontBrushDesc brushDesc;
	brushDesc.Color = color;

	FontBrushDesc* findBrush = NULL;
	for (FontBrushDesc& desc : fontBrush)
	{
		if (desc == brushDesc)
		{
			findBrush = &desc;
			break;
		}
	}

	if (findBrush == NULL)
	{
		D2D1::ColorF colorF = D2D1::ColorF(color.r, color.g, color.b);
		deviceContext->CreateSolidColorBrush(colorF, &brushDesc.Brush);

		fontBrush.push_back(brushDesc);
		findBrush = &brushDesc;
	}


	FontTextDesc textDesc;
	textDesc.Font = font;
	textDesc.FontSize = size;
	textDesc.Stretch = stretch;
	textDesc.Style = style;
	textDesc.Weight = weight;

	FontTextDesc* findText = NULL;
	for (FontTextDesc& desc : fontText)
	{
		if (desc == textDesc)
		{
			findText = &desc;
			break;
		}
	}

	if (findText == NULL)
	{
		writeFactory->CreateTextFormat
		(
			textDesc.Font.c_str(), NULL, textDesc.Weight, textDesc.Style, textDesc.Stretch, textDesc.FontSize,
			L"ko", &textDesc.Format
		);

		fontText.push_back(textDesc);
		findText = &textDesc;
	}

	D2D1_RECT_F rectF;
	rectF.left = (float)rect.left;
	rectF.right = (float)rect.right;
	rectF.top = (float)rect.top;
	rectF.bottom = (float)rect.bottom;


#ifdef UNICODE
	deviceContext->DrawTextW
	(
		text.c_str(), text.size(), findText->Format, rectF, findBrush->Brush
	);
#else
	deviceContext->DrawTextA
	(
		text.c_str(), text.size(), findText->Format, rectF, findBrush->Brush
	);
#endif

	
}

WriteManager::WriteManager()
{
	HRESULT hr;

	hr = DWriteCreateFactory
	(
		DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown **)&writeFactory
	);
	assert(SUCCEEDED(hr));


	D2D1_FACTORY_OPTIONS option;
	option.debugLevel = D2D1_DEBUG_LEVEL_NONE;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);
	assert(SUCCEEDED(hr));

	IDXGIDevice* dxgiDevice;
	hr = Device->QueryInterface(&dxgiDevice);
	assert(SUCCEEDED(hr));

	hr = factory->CreateDevice(dxgiDevice, &device);
	assert(SUCCEEDED(hr));

	hr = device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS, &deviceContext);
	assert(SUCCEEDED(hr));

	IDXGISurface* dxgiSurface;
	hr = SwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void **)&dxgiSurface);
	assert(SUCCEEDED(hr));


	D2D1_BITMAP_PROPERTIES1 bp;
	bp.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
	bp.dpiX = 96;
	bp.dpiY = 96;
	bp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	bp.colorContext = NULL;

	hr = deviceContext->CreateBitmapFromDxgiSurface(dxgiSurface, &bp, &targetBitmap);
	assert(SUCCEEDED(hr));

	deviceContext->SetTarget(targetBitmap);
}


WriteManager::~WriteManager()
{
	for (FontBrushDesc desc : fontBrush)
		SAFE_RELEASE(desc.Brush);

	for (FontTextDesc desc : fontText)
		SAFE_RELEASE(desc.Format);


	SAFE_RELEASE(targetBitmap);

	SAFE_RELEASE(factory);
	SAFE_RELEASE(writeFactory);

	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(device);
}
