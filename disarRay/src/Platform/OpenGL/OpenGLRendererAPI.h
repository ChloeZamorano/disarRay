#pragma once

#include "DrayIntern.h"

#include "Renderer/RendererAPI.h"

namespace Dray
{
	class DRAY_API OpenGLRendererAPI : public RendererAPI
	{
	public:
		void SetClearColor(f32 r, f32 g, f32 b) override;
		void SetClearColor(f32 r, f32 g, f32 b, f32 a) override;
		void SetClearColor(const glm::vec3& col) override;
		void SetClearColor(const glm::vec4& col) override;
		void Clear() override;

		void DrawIndexed(const std::shared_ptr<VertexArray>& vao) override;
	};
}
