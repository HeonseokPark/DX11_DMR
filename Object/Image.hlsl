cbuffer VS_Vp : register(b0)
{
    matrix View;
    matrix Projection;
}

cbuffer VS_World : register(b1)
{
    matrix World;
}
cbuffer VS_FrameUv : register(b2)
{
    float4 FrameUv;
}
cbuffer PS_Color : register(b0)
{
    float4 Color;
}

struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : UV0;
};

struct PixelInput
{
    float4 Position : SV_POSITION;
    float2 Uv : UV0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    output.Uv = input.Uv;

    return output;
}
PixelInput VS2(VertexInput input)
{
    PixelInput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    output.Uv = input.Uv;

    if (output.Uv.x == 0.0f)
    {
        output.Uv.x = FrameUv.x;
    }
    if (output.Uv.x == 1.0f)
    {
        output.Uv.x = FrameUv.z;
    }
    if (output.Uv.y == 0.0f)
    {
        output.Uv.y = FrameUv.y;
    }
    if (output.Uv.y == 1.0f)
    {
        output.Uv.y = FrameUv.w;
    }
    
    return output;
}
//��������
//���÷��� ��� �ȼ��� ó���Ǵ���
SamplerState Sampler : register(s0);
//�ؽ��� �ڿ�
Texture2D Texture : register(t0);

//�׳� �ؽ���
float4 PS(PixelInput input) : SV_TARGET
{
    //SamplerState.
    float4 color = Texture.Sample(Sampler, input.Uv);
    //SSampler.
    if(any(color))
    {
        //�Ǽ� ������ ���ϸ� ���Ҽ��� ��ο� ����
        //color = color * Color;
        //��ο� ���� ������ �ݴ밪 ��� ���Ҽ��� �����
        color.r = (1.0f - ((1.0f - color.r) * (1.0f - Color.r)));
        color.g = (1.0f - ((1.0f - color.g) * (1.0f - Color.g)));
        color.b = (1.0f - ((1.0f - color.b) * (1.0f - Color.b)));
        color.a = color.a * Color.a;
    }
    return color;
}
//��� �����
float4 PS2(PixelInput input) : SV_TARGET
{
    float4 color= Texture.Sample(Sampler, input.Uv);

    if (color.r > 0.9f && color.g < 0.1f && color.b > 0.9f)
    {
        color= 0.0f;
    }
    if (any(color))
    {
        //�Ǽ� ������ ���ϸ� ���Ҽ��� ��ο� ����
        //color = color * Color;
        //��ο� ���� ������ �ݴ밪 ��� ���Ҽ��� �����
        color.r = (1.0f - ((1.0f - color.r) * (1.0f - Color.r)));
        color.g = (1.0f - ((1.0f - color.g) * (1.0f - Color.g)));
        color.b = (1.0f - ((1.0f - color.b) * (1.0f - Color.b)));
        color.a = color.a * Color.a;
    }
    return color;
}

//�׸���
float4 PS3(PixelInput input) : SV_TARGET
{
    float4 color = Texture.Sample(Sampler, input.Uv);

    if (color.r > 0.9f && color.g < 0.1f && color.b > 0.9f)
    {
        color= 0.0f;
    }
    else if (any(color))
    {
        color.r = 0.0f;
        color.g = 0.0f;
        color.b = 0.0f;
    }

    return color;
}