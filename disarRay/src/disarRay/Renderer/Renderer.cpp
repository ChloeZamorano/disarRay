#include "drpch.h"
#include "Renderer.h"

namespace Dray
{
	void Renderer::BeginScene()
	{
	}
	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vao)
	{
		RenderCommand::DrawIndexed(vao);
	}
}
