#include "stdafx.h"
#include "Image.h"


Image::Image(_tstring file, string ps):parent(nullptr)
{
	ZeroMemory(&angle, sizeof(angle));
	ZeroMemory(&angle2, sizeof(angle));

	vertices = new Vertex[VertexCount];
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);

	//uv ��ǥ�� ���ʻ���� 0,0 �ִ밪�� 1�̴�.
	vertices[0].Uv = D3DXVECTOR2(0.0f, 1.0f);
	vertices[1].Uv = D3DXVECTOR2(0.0f, 0.0f);
	vertices[2].Uv = D3DXVECTOR2(1.0f, 1.0f);
	vertices[3].Uv = D3DXVECTOR2(1.0f, 1.0f);
	vertices[4].Uv = D3DXVECTOR2(0.0f, 0.0f);
	vertices[5].Uv = D3DXVECTOR2(1.0f, 0.0f);

	HRESULT hr;

	//���ؽ� ���� ����
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.ByteWidth = sizeof(Vertex) * VertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}
	//�÷����� ����
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(ColorBufferDesc);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		HRESULT hr = Device->CreateBuffer(&desc, NULL, &colorBuffer);
		assert(SUCCEEDED(hr));
	}
	//���� ����
	{
		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));
		//���� ��� ����
		desc.RenderTarget[0].BlendEnable = false;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Device->CreateBlendState(&desc, &blendState[0]);
		//���� ��� �ѱ�
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Device->CreateBlendState(&desc, &blendState[1]);
	}



	shader = new Shader(_T("./Object/Image.hlsl"),"VS", ps);
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	shader->CreateInputLayout(LayoutDesc, 2);

	_tstring textureFile = _T("./images/") + file;

	D3DX11CreateShaderResourceViewFromFile(
		Device,//����̽�
		textureFile.c_str(),//���� ��� �̸�
		NULL,//�߰����� �̹��� ����(NULL ���� ����ũ�� ���)
		NULL,//�ΰ�
		&srv,//������ ���̴� ���ҽ��� �ڿ�
		&hr
	);
	assert(SUCCEEDED(hr)&& "���ҽ� �ڿ� �� ���� ����");

}


Image::Image(_tstring file, UINT MaxFrameX, UINT MaxFrameY, string ps)
	: parent(nullptr)
{
	ZeroMemory(&angle, sizeof(angle));
	ZeroMemory(&angle2, sizeof(angle));
	vertices = new Vertex[VertexCount];
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);

	//uv ��ǥ�� ���ʻ���� 0,0 �ִ밪�� 1�̴�
	vertices[0].Uv = D3DXVECTOR2(0.0f, 1.0f);
	vertices[1].Uv = D3DXVECTOR2(0.0f, 0.0f);
	vertices[2].Uv = D3DXVECTOR2(1.0f, 1.0f);
	vertices[3].Uv = D3DXVECTOR2(1.0f, 1.0f);
	vertices[4].Uv = D3DXVECTOR2(0.0f, 0.0f);
	vertices[5].Uv = D3DXVECTOR2(1.0f, 0.0f);


	HRESULT hr;

	//���ؽ� ���� ����
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.ByteWidth = sizeof(Vertex) * VertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}
	//�÷����� ����
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(ColorBufferDesc);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		HRESULT hr = Device->CreateBuffer(&desc, NULL, &colorBuffer);
		assert(SUCCEEDED(hr));
	}
	//���� ����
	{
		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));

		desc.RenderTarget[0].BlendEnable = false;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Device->CreateBlendState(&desc, &blendState[0]);

		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Device->CreateBlendState(&desc, &blendState[1]);
	}


	//������uv ���� ����
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(FrameUvBufferDesc);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		hr = Device->CreateBuffer(&desc, NULL, &FrameUvBuffer);
		assert(SUCCEEDED(hr));
	}
	maxFrameX = MaxFrameX;
	maxFrameY = MaxFrameY;

	shader = new Shader(_T("./Object/image.hlsl"), "VS2", ps);
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	shader->CreateInputLayout(LayoutDesc, 2);


	_tstring textureFile = _T("./images/") + file;
	//�ؽ���(�̹�������)�� �о srv�� ����
	D3DX11CreateShaderResourceViewFromFile
	(
		Device,//����̽�
		textureFile.c_str(),//�����̸�
		NULL, //�߰����� �̹��� ���� NULL���� ����ũ��
		NULL,//NULL ��
		&srv,//���̴��ڿ�
		&hr
	);
	assert(SUCCEEDED(hr));


}

Image::~Image()
{
	SAFE_DELETE(shader);
	SAFE_DELETE_ARRAY(vertices);
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(FrameUvBuffer);
	SAFE_RELEASE(colorBuffer);
	SAFE_RELEASE(blendState[1]);
	SAFE_RELEASE(blendState[0]);
}

void Image::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Image::Position(D3DXVECTOR2 vec)
{
	position = vec;
}

void Image::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Image::Scale(D3DXVECTOR2 vec)
{
	scale = vec;
}


void Image::Rotate(D3DXVECTOR3 x)
{
	angle = x;
}
void Image::Rotate(float x, float y, float z)
{
	Rotate(D3DXVECTOR3(x, y, z));
}
void Image::Rotate2(D3DXVECTOR3 x)
{
	angle2 = x;
}
void Image::Rotate2(float x, float y, float z)
{
	Rotate2(D3DXVECTOR3(x, y, z));
}

void Image::Update()
{
	D3DXMATRIX S, R, T, W, R2;
	D3DXMatrixScaling(&S, scale.x, scale.y, 1);
	D3DXMatrixRotationYawPitchRoll(&R, angle.y, angle.x, angle.z);
	D3DXMatrixTranslation(&T, position.x, position.y, 0);
	D3DXMatrixRotationYawPitchRoll(&R2, angle2.y, angle2.x, angle2.z);
	W = S * R * T * R2;
	RT = R * T * R2;
	if (parent)
	{
		W *= *parent;
		RT *= *parent;
	}
	shader->World(W);
}

void Image::Render()
{
	Update();
	UINT stride = sizeof(Vertex);
	UINT offset = 0;


	//���� ��
	DeviceContext->UpdateSubresource(colorBuffer, 0, NULL, &colorBufferData, 0, 0);
	DeviceContext->PSSetConstantBuffers(0, 1, &colorBuffer);


	//�������� �ִ� �̹��� ���
	if (maxFrameX != 1 || maxFrameY != 1)
	{
		FrameUvBufferData.FrameUv.x = 1.0f / maxFrameX * CurrentFrameX;
		FrameUvBufferData.FrameUv.y = 1.0f / maxFrameY * CurrentFrameY;
		FrameUvBufferData.FrameUv.z = 1.0f / maxFrameX * (CurrentFrameX + 1);
		FrameUvBufferData.FrameUv.w = 1.0f / maxFrameY * (CurrentFrameY + 1);
		DeviceContext->UpdateSubresource(FrameUvBuffer, 0, NULL, &FrameUvBufferData, 0, 0);
		DeviceContext->VSSetConstantBuffers(2, 1, &FrameUvBuffer);
	}


	shader->SetBuffers();
	//�ȼ� ���̴��� ���̴� ���ҽ� �� ���� ����
	DeviceContext->PSSetShaderResources(0,	//��ŸƮ ����
		1,		//���ҽ� ����
		&srv);//���̴� ���ҽ� ��
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//���� �ѱ�
	DeviceContext->OMSetBlendState(blendState[1], NULL, 0xff);
	DeviceContext->Draw(VertexCount, 0);
	//���� ����
	DeviceContext->OMSetBlendState(blendState[0], NULL, 0xff);
}

void Image::LoofRender(float x, float y)
{
	//�̹��� ��ǥ�� ����� �ʰ� ���� ����ֱ�
	if (x > 1.0f) x -= floorf(x);
	if (y > 1.0f) y -= floorf(y);
	if (x < 0.0f)
	{
		//���� ��ȣ ����
		x = fabsf(x);
		//			�Ҽ��� ���� ���� ������ �ϱ�
		x = 1.0f - (x - floorf(x));
	}
	if (y < 0.0f)
	{
		//���� ��ȣ ����
		y = fabsf(y);
		//			�Ҽ��� ���� ���� ������ �ϱ�
		y = 1.0f - (y - floorf(y));
	}
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	//���� �ѱ�
	DeviceContext->OMSetBlendState(blendState[1], NULL, 0xff);
	//�ȼ� ���̴��� ���̴� ���ҽ� �� �� ����
	DeviceContext->PSSetShaderResources(0,//��ŸƮ ����
		1,//���ҽ� ����
		&srv);//���̴� ���ҽ� ��
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//���� ������� �����ϰ� ������ ���� ������ ���´�
	D3DXVECTOR2 tempSize = scale;
	D3DXVECTOR2 tempPos = position;


	//���� ��
	DeviceContext->UpdateSubresource(colorBuffer, 0, NULL, &colorBufferData, 0, 0);
	DeviceContext->PSSetConstantBuffers(0, 1, &colorBuffer);
	
	//�� ��� �̹���
	
	FrameUvBufferData.FrameUv.x = x;
	FrameUvBufferData.FrameUv.y = y;
	FrameUvBufferData.FrameUv.z = 1.0f;
	FrameUvBufferData.FrameUv.w = 1.0f;
	DeviceContext->UpdateSubresource(FrameUvBuffer, 0, NULL, &FrameUvBufferData, 0, 0);
	DeviceContext->VSSetConstantBuffers(2, 1, &FrameUvBuffer);
	scale.x = tempSize.x * (1.0f - x);
	scale.y = tempSize.y * (1.0f - y);
	position.x = position.x - (tempSize.x - scale.x)*0.5f;
	position.y = position.y + (tempSize.y - scale.y)*0.5f;
	Update();
	shader->SetBuffers();
	DeviceContext->Draw(VertexCount, 0);
	//���� ������ �����ֱ�
	scale = tempSize;
	position = tempPos;

	//���� �̹���
	if (x != 0.0f)
	{
		FrameUvBufferData.FrameUv.x = 0.0f;
		FrameUvBufferData.FrameUv.y = y;
		FrameUvBufferData.FrameUv.z = x;
		FrameUvBufferData.FrameUv.w = 1.0f;
		DeviceContext->UpdateSubresource(FrameUvBuffer, 0, NULL, &FrameUvBufferData, 0, 0);
		DeviceContext->VSSetConstantBuffers(2, 1, &FrameUvBuffer);
		scale.x = tempSize.x * x;
		scale.y = tempSize.y * (1.0f - y);
		position.x = position.x + (tempSize.x - scale.x)*0.5f;
		position.y = position.y + (tempSize.y - scale.y)*0.5f;
		Update();
		shader->SetBuffers();
		DeviceContext->Draw(VertexCount, 0);
		//���� ������ �����ֱ�
		scale = tempSize;
		position = tempPos;
	}
	//���ϴ� �̹���
	if (y != 0.0f)
	{
		FrameUvBufferData.FrameUv.x = x;
		FrameUvBufferData.FrameUv.y = 0.0f;
		FrameUvBufferData.FrameUv.z = 1.0f;
		FrameUvBufferData.FrameUv.w = y;
		DeviceContext->UpdateSubresource(FrameUvBuffer, 0, NULL, &FrameUvBufferData, 0, 0);
		DeviceContext->VSSetConstantBuffers(2, 1, &FrameUvBuffer);
		scale.x = tempSize.x * (1.0f - x);
		scale.y = tempSize.y * y;
		position.x = position.x - (tempSize.x - scale.x)*0.5f;
		position.y = position.y - (tempSize.y - scale.y)*0.5f;
		Update();
		shader->SetBuffers();
		DeviceContext->Draw(VertexCount, 0);
		//���� ������ �����ֱ�
		scale = tempSize;
		position = tempPos;

		//�̹��� ��ǥ ����� �Ŀ� �ڸ���.
	}

	//���ϴ� �̹���
	if (y != 0.0f && x != 0.0f)
	{
		FrameUvBufferData.FrameUv.x = 0.0f;
		FrameUvBufferData.FrameUv.y = 0.0f;
		FrameUvBufferData.FrameUv.z = x;
		FrameUvBufferData.FrameUv.w = y;
		DeviceContext->UpdateSubresource(FrameUvBuffer, 0, NULL, &FrameUvBufferData, 0, 0);
		DeviceContext->VSSetConstantBuffers(2, 1, &FrameUvBuffer);
		scale.x = tempSize.x * x;
		scale.y = tempSize.y * y;
		position.x = position.x + (tempSize.x - scale.x)*0.5f;
		position.y = position.y - (tempSize.y - scale.y)*0.5f;
		Update();
		shader->SetBuffers();
		DeviceContext->Draw(VertexCount, 0);
		//���� ������ �����ֱ�
		scale = tempSize;
		position = tempPos;
	}

	//���� ����
	DeviceContext->OMSetBlendState(blendState[0], NULL, 0xff);
}

void Image::PlayAnimation(PlayState ps, bool isFrameX, float nexttime)
{
	//�ð� ����
	time += g_ETime;
	//���� �̹����� �Ѿ �ð��� ��ٸ�
	if (time >= nexttime)
	{
		time -= nexttime;
		//x�� ���ϴ� �̹��� ���
		if (isFrameX)
		{
			switch (ps)
			{
			case ANI_LOOP:
				if (maxFrameX - 1 > CurrentFrameX)
					CurrentFrameX++;
				else
					CurrentFrameX = 0;
					break;
			case ANI_REVERSE:
				if (CurrentFrameX > 0)
					CurrentFrameX--;
				else
					CurrentFrameX = maxFrameX - 1;
				break;
			}
		}
		//y�� ���ϴ� �̹��� ���
		else
		{
			switch (ps)
			{
			case ANI_LOOP:
				if (maxFrameY - 1 > CurrentFrameY)
					CurrentFrameY++;
				else
					CurrentFrameY = 0;
				break;
			case ANI_REVERSE:
				if (CurrentFrameY > 0)
					CurrentFrameY--;
				else
					CurrentFrameY = maxFrameY - 1;
				break;
			}
		}

	}
	Render();
}

void Image::Color(float r, float g, float b, float a)
{
	Color(D3DXCOLOR(r, g, b, a));
}

void Image::Color(D3DXCOLOR vec)
{
	colorBufferData.Color = vec;
}