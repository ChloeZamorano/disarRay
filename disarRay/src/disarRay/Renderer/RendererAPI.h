#pragma once

#include "DrayIntern.h"

#include "VertexArray.h"
#include <glm/glm.hpp>

namespace Dray
{
	class DRAY_API RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1,
			DirectX11 = 2,
			DirectX12 = 3,
			Vulkan = 4,
			Metal = 5,
		};

		virtual void SetClearColor(f32 r, f32 g, f32 b) = 0;
		virtual void SetClearColor(f32 r, f32 g, f32 b, f32 a) = 0;
		virtual void SetClearColor(const glm::vec3& col) = 0;
		virtual void SetClearColor(const glm::vec4& col) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vao) = 0;

		static inline API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}
