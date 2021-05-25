#include "drpch.h"
#include "VertexArray.h"

#include "Rasterizer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Dray
{
	VertexArray* VertexArray::Create()
	{
		switch (Rasterizer::GetAPI())
		{
		case RasterizerAPI::OpenGL:
			return new OpenGLVertexArray();

		default:
			DRAY_ENGINE_ASSERT(false, "Graphics API unsupported or null.")
			return nullptr;
		}
	}
}