#include "drpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Dray
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();

		default:
			DRAY_ENGINE_ASSERT(false, "Graphics API unsupported or null.")
			return nullptr;
		}
	}
}