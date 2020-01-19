//���̴� ������ Ư�� �������Ϳ� �������� �Ҵ��ϱ����� ������ Ű���� �ε��� �����Ͽ� �����Ͽ� ��� ����
//b	Constant buffer
//t Texture and texturebuffer
//������۴� ����ü�� �������¸� ������
cbuffer VS_Vp : register(b0)
{
    matrix View;
    matrix Projection;
}

cbuffer VS_World : register(b1)
{
    matrix World;
}

cbuffer PS_Color : register(b0)
{
    float4 Color;
}

struct VertexInput
{
    float4 Position : POSITION0;
};

struct PixelInput
{
    float4 Position : SV_POSITION;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    return Color;
}

