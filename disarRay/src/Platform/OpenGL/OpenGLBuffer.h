#pragma once

#include "DrayIntern.h"

#include "Rasterizer/Buffer.h"

namespace Dray
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(f32* verts, u32 size);
		~OpenGLVertexBuffer();

		virtual VertexLayout& GetLayout() override { return m_Layout;  }
		virtual void SetLayout(VertexLayout& layout) override { m_Layout = layout; }

		void Bind() const override;
		void Unbind() const override;

	private:
		u32 m_RenderID;
		VertexLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(u32* indices, u32 count);
		~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;

		u32 GetCount() const override { return m_Count; }

	private:
		u32 m_RenderID;
		u32 m_Count;
	};
}
