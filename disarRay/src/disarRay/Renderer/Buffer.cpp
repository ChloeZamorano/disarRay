#include "drpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Dray
{
	VertexBuffer* VertexBuffer::Create(f32* verts, u32 size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(verts, size);

		default:
			return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(u32* indices, u32 count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);

		default:
			return nullptr;
		}
	}
}
