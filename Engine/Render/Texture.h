#pragma once

#include "Core/Type.h"
#include <string>
#include <d3d11.h>
#include <memory>

namespace Blue
{
	struct TextureData
	{
		TextureData() = default;
		~TextureData()
		{
			//���� ���ҽ� ����
			free(data);
			
			shaderResourceView->Release();
			shaderResourceView = nullptr;

			samplerState->Release();
			samplerState = nullptr;
		}

		//�ؽ�ó ���� ������
		int32 width = 0;
		int32 height = 0;
		int32 channelCount = 0; //RGB or RGBA�� 
		void* data = nullptr;

		//DX ���ҽ�
		ID3D11ShaderResourceView* shaderResourceView = nullptr;
		//���ø� ����
		ID3D11SamplerState* samplerState = nullptr;
	};

	class Texture
	{
		//���ε��� ���̴� ������
		enum class BindType
		{
			VertexShader,
			PixelShader
		};

	public:
		Texture();
		Texture(const std::string& name, BindType bindType = BindType::PixelShader, uint32 index = 0u);
		~Texture();

		void Bind();

	private:
		void LoadTexture(const std::string& name);

	private:
		std::string name;
		uint32 index = 0u;
		BindType bindType = BindType::PixelShader;
		
		std::unique_ptr<TextureData> textureData;
	};
}