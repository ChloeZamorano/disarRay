#pragma once

#include "DrayIntern.h"

#include "Rasterizer/RasterContext.h"

struct GLFWwindow;

namespace Dray
{
	class DRAY_API OpenGLContext : public RasterContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void ClearColor(f32 r, f32 g, f32 b, f32 a) override;
		void SwapBuffers() override;
		
	private:
		GLFWwindow* m_WindowHandle;
	};
}
