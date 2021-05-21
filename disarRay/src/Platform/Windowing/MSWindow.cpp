#include "drpch.h"
#include "MSWindow.h"

#include <glad/glad.h>

#include "DrayIntern.h"
#include "Events/AppEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Dray
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int err, const char* msg)
	{
		DRAY_ENGINE_ERROR("GLFW Error ({2}): {3}", err, msg);
	}

	Window* Window::Create(const WindowProps& data)
	{
		return new MSWindow(data);
	}

	MSWindow::MSWindow(const WindowProps& data)
	{
		Init(data);
	}

	MSWindow::~MSWindow()
	{
		Shutdown();
	}

	void MSWindow::Init(const WindowProps& data)
	{
		// Set window metadata
		m_Data.Title = data.Title;
		m_Data.Width = data.Width;
		m_Data.Height = data.Height;
	
		DRAY_ENGINE_INFO("Creating MS Window \"{2}\" ({3}, {4})", data.Title, data.Width, data.Height);
		
		// Initialize GLFW
		if (!s_GLFWInitialized)
		{
			DRAY_ENGINE_VERIFY(glfwInit(),
				"Could not initialize GLFW!",
				"GLFW initialized correctly!")

			glfwSetErrorCallback(GLFWErrorCallback);
		
			s_GLFWInitialized = true;
		}
		
		// Create window, as well as a couple other minor things
		m_Window = glfwCreateWindow(data.Width, data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		DRAY_ENGINE_VERIFY(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress),
			"Could not initialize Glad!",
			"Glad initialized correctly!")

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		DRAY_ENGINE_INFO("OpenGL version: {2}", glGetString(GL_VERSION));
		DRAY_ENGINE_INFO("GLFW version: {2}.{3}.{4}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);

		// GLFW Callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* wdw, int w, int h)
			{
				WindowData& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(wdw));
				data.Width = (u32)w;
				data.Height = (u32)h;

				WindowResizeEvent e((u32)w, (u32)h);
				data.EventCallback(e);
			});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* wdw)
			{
				WindowData& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(wdw));
				WindowCloseEvent e;

				data.EventCallback(e);
			});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* wdw, int key, int scan, int action, int mods)
			{
				WindowData& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(wdw));

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyDownEvent e(key, 0);
						data.EventCallback(e);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyDownEvent e(key, 1);
						data.EventCallback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyUpEvent e(key);
						data.EventCallback(e);
						break;
					}
				}
			});
		glfwSetCharCallback(m_Window, [](GLFWwindow* wdw, unsigned int character)
			{
				WindowData& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(wdw));
				KeyTypedEvent e(character);
				data.EventCallback(e);
			});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* wdw, int btn, int action, int mods)
			{
				WindowData& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(wdw));

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonDownEvent e(btn);
						data.EventCallback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonUpEvent e(btn);
						data.EventCallback(e);
						break;
					}
				}
			});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* wdw, f64 x, f64 y)
			{
				WindowData& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(wdw));

				MouseScrolledEvent e((f32)x, (f32)y);
				data.EventCallback(e);
			});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* wdw, f64 x, f64 y)
			{
				WindowData& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(wdw));

				MouseMovedEvent e((f32)x, (f32)y);
				data.EventCallback(e);
			});
	}

	void MSWindow::Shutdown()
	{
		DRAY_ENGINE_INFO("Destroying MS Window...");
		glfwDestroyWindow(m_Window);
		DRAY_ENGINE_INFO("MS Window destroyed.");

		DRAY_ENGINE_INFO("Terminating GLFW...");
		glfwTerminate();
		DRAY_ENGINE_INFO("GLFW terminated.");
	}

	void MSWindow::RenderUpdate(LayerStack& stack)
	{
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		for (Layer* layer : stack)
			layer->OnUpdate();

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void MSWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled ? 1 : 0);

		m_Data.VSync = enabled;
		DRAY_ENGINE_INFO("VSync: {0}", IsVSync());
	}

	bool MSWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}
