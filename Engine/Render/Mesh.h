#pragma once

#include <vector>
#include <memory>
#include <d3d11.h>
#include "Vertex.h"
#include "../Core/Type.h"
#include "Math/Transform.h"

namespace Blue
{
	// 메쉬 데이터 구조체.
	struct MeshData
	{
		MeshData();
		MeshData(
			const std::vector<Vertex>& vertices,
			const std::vector<uint32>& indices
		);
		~MeshData();

		void Bind();
		uint32 IndexCount() const { return (uint32)indices.size(); }

		// 정점 데이터를 업데이트하는 함수.
		void UpdateVertexBuffer(const std::vector<Vertex>& vertices);

		// 정점 데이터.
		std::vector<Vertex> vertices;
		uint32 stride = 0;
		ID3D11Buffer* vertexBuffer = nullptr; // 메모리 덩어리

		// 인덱스 데이터.              (점의 순서)
		std::vector<uint32> indices;
		ID3D11Buffer* indexBuffer = nullptr;
	};

	class Mesh
	{
	public:
		Mesh();
		virtual ~Mesh() = default;

		virtual void Draw();

		//@Temp : 트랜스폼 정보(임시) -> 현재 엑터가 없어서 임시로
		Transform transform;



	protected:
		//std::vector<std::shared_ptr<MeshData>> meshes;
		std::vector<std::weak_ptr<MeshData>> meshes; // 데이터를 가지는건 똑같은데, 약한참조(같은 모델은 복사하지 않음)
		//std::vector<std::shared_ptr<class Shader>> shaders;
		std::vector<std::weak_ptr<class Shader>> shaders;
	};
}