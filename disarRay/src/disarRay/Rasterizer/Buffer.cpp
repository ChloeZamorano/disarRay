#include "drpch.h"
#include "Buffer.h"

#include "Rasterizer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Dray
{
	VertexBuffer* VertexBuffer::Create(f32* verts, u32 size)
	{
		switch (Rasterizer::GetAPI())
		{
		case RasterizerAPI::None:
			return nullptr;

		case RasterizerAPI::OpenGL:
			return new OpenGLVertexBuffer(verts, size);

		default:
			return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(u32* indices, u32 count)
	{
		switch (Rasterizer::GetAPI())
		{
		case RasterizerAPI::None:
			return nullptr;

		case RasterizerAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, count);

		default:
			return nullptr;
		}
	}
}
