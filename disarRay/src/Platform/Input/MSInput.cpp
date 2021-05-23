#include "drpch.h"
#include "MSInput.h"

#include "App/DrayApp.h"
#include <GLFW/glfw3.h>

namespace Dray
{
	Input* Input::s_Instance;

	bool Input::MakePoller()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new MSInput();
			return true;
		}
		return false;
	}

	bool MSInput::GetKeyImpl(u32 keycode)
	{
		u32 state = glfwGetKey(
			statc(GLFWwindow*, DrayApp::Get().GetWindow().GetNativeWindow()),
			keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool MSInput::GetMouseButtonImpl(u32 button)
	{
		u32 state = glfwGetMouseButton(
			statc(GLFWwindow*, DrayApp::Get().GetWindow().GetNativeWindow()),
			button);
		return state == GLFW_PRESS;
	}

	glm::vec2 MSInput::GetMousePosImpl()
	{
		double x = 0, y = 0;
		glfwGetCursorPos(
			statc(GLFWwindow*, DrayApp::Get().GetWindow().GetNativeWindow()),
			&x, &y);

		glm::vec2 out = glm::vec2((f32)x, (f32)y);
		return out;
	}
}
