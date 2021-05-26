#pragma once

#include "DrayIntern.h"

namespace Dray
{
	class DRAY_API Shader
	{
	public:
		Shader(str8 vertexSrc, str8 pixelSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		u32 m_RenderID;
	};
}