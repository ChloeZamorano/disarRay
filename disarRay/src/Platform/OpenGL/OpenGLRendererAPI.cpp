#include "drpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Dray
{
	void OpenGLRendererAPI::SetClearColor(f32 r, f32 g, f32 b)
	{
		glClearColor(r, g, b, 1);
	}

	void OpenGLRendererAPI::SetClearColor(f32 r, f32 g, f32 b, f32 a)
	{
		glClearColor(r, g, b, a);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec3& col)
	{
		glClearColor(col.r, col.g, col.b, 1);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& col)
	{
		glClearColor(col.r, col.g, col.b, col.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vao)
	{
		vao->Bind();
		glDrawElements(GL_QUADS, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
