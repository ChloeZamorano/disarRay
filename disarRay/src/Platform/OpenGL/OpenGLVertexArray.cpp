#include "drpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Dray
{
	static GLenum ShaderDataTypeToGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return GL_INT;

		case ShaderDataType::Uint:
		case ShaderDataType::Uint2:
		case ShaderDataType::Uint3:
		case ShaderDataType::Uint4:
			return GL_UNSIGNED_INT;

		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:
			return GL_FLOAT;

		default:
			DRAY_ENGINE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RenderID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RenderID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RenderID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		DRAY_ENGINE_ASSERT(vertexBuffer->GetLayout().GetElements().size(),
			"Vertex buffer has no layout.")

		glBindVertexArray(m_RenderID);
		vertexBuffer->Bind();

		u32 i = 0;
		auto layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i,
				element.GetComponentCount(),
				ShaderDataTypeToGLBaseType(element.Type),
				element.Normalized ? 1 : 0,
				layout.GetStride(),
				(const void*)element.Offset);
			i++;
		}

		m_VertexBuffers.push_back(vertexBuffer);

		glBindVertexArray(0);
		vertexBuffer->Unbind();
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RenderID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
		glBindVertexArray(0);
		indexBuffer->Unbind();
	}
}