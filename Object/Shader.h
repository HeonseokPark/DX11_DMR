#pragma once
//��ü���� �ٸ� ����,�ٸ� ���̴�,�ٸ� ��ǲ ���̾ƿ��� �����Ͽ� ����Ҽ� �ְԲ� ���� Ŭ����
class Shader
{
private:
	D3DXMATRIX world;

	ID3D11InputLayout* vertexLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	
	ID3D10Blob* vsBlob;
	ID3D10Blob* psBlob;
public:
	Shader(_tstring file, string vs = "VS", string ps = "PS");
	~Shader(); 
	void World(D3DXMATRIX& world);
	void CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT count);

	void SetBuffers();
	struct WorldBufferDesc
	{
	public:
		WorldBufferDesc()
		{
			D3DXMatrixIdentity(&World);
		}

		D3DXMATRIX World;
	} worldBufferData;

	ID3D11Buffer* worldBuffer;
};

