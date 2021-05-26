#pragma once

#include "DrayIntern.h"

#include "RenderCommand.h"

namespace Dray
{
	class DRAY_API Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vao);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}
