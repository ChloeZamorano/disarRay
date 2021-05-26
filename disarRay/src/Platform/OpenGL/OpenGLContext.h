#pragma once

#include "DrayIntern.h"

#include "Renderer/RenderContext.h"

struct GLFWwindow;

namespace Dray
{
	class DRAY_API OpenGLContext : public RenderContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
		
	private:
		GLFWwindow* m_WindowHandle;
	};
}
