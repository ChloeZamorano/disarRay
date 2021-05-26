#pragma once

#include "DrayIntern.h"

#include "RendererAPI.h"

namespace Dray
{
	class DRAY_API RenderCommand
	{
	public:
		inline static void SetClearColor(f32 r, f32 g, f32 b)
		{
			s_RendererAPI->SetClearColor(r, g, b);
		}

		inline static void SetClearColor(f32 r, f32 g, f32 b, f32 a)
		{
			s_RendererAPI->SetClearColor(r, g, b, a);
		}

		inline static void SetClearColor(const glm::vec3& col)
		{
			s_RendererAPI->SetClearColor(col);
		}

		inline static void SetClearColor(const glm::vec4& col)
		{
			s_RendererAPI->SetClearColor(col);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vao)
		{
			s_RendererAPI->DrawIndexed(vao);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}