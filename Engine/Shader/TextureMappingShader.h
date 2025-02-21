#pragma once

#include "Shader.h"
#include <memory>

namespace Blue
{
	class TextureMappingShader : public Shader
	{
	public:
		TextureMappingShader();
		TextureMappingShader(const std::string& textureName);

		virtual void Bind() override;

	private:
		std::unique_ptr<class Texture> texture;
	};
}