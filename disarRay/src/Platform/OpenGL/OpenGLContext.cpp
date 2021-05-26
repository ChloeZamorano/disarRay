#include "drpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Dray
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) :
		m_WindowHandle(windowHandle) {}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		DRAY_ENGINE_INFO("OpenGL: {2}", glGetString(GL_RENDERER));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
