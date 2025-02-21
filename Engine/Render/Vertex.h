#pragma once
#include "Math/Vector3.h" //������ �켱
#include "Math/Vector2.h"

//�ؽ�ó���� = �ؽ��ʹ� 2���� ������Ʈ�� 3���� = 2->3, 3->2;
//UV��ǥ = �ؽ�ó�� ��ǥ
//UV���� = �ؽ�ó�� ������Ʈ�� 1:1 ���� �� �� �ְ� ������ִ� 

//���� ���ε� => ������ => ���ҽ� => vs,ps =>
//RGB = ����� ������ ���

namespace Blue
{
	class Vertex // data�� ����, 
	{
	public:
		Vertex(const Vector3& position, const Vector3& color, const Vector2& texCoord)
			: position(position), color(color),texCoord(texCoord) //���� ���̴��� �ٲ�� inputlayout�� ���� �ٲ�����
		{

		}
		static unsigned int Stride() { return sizeof(Vertex); }

	public:
		//���� ��ġ
		Vector3 position;
		//���� ����
		Vector3 color;
		//���� ���� �ؽ�ó ��ǥ
		Vector2 texCoord;
	};
}