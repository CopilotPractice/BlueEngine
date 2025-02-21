struct VertexInput  // cpu���� VertexInput���� �Ѿ��
{
    //POSITION �̰� �ڵ��ϼ����� POSITIONT�� ��
    float3 position : POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
};

struct VertexOutPut //���� shader�� �Է��� pixel�� ���
{
    float4 position : SV_Position; //�ø�ƽ
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
};

VertexOutPut main(VertexInput input) //�����ܰ� ������� ������ �Է����� �޾ƾ� ��.
{
    VertexOutPut output;
    output.position = float4(input.position, 1);
    output.color = input.color;
    output.texCoord = input.texCoord;
    
    return output;
}