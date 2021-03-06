#include "drpch.h"
#include "ImGuiLayer.h"

#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "App/DrayApp.h"

// TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Dray
{
	ImGuiLayer::ImGuiLayer() :
		Layer("ImGuiLayer") {}

	ImGuiLayer::~ImGuiLayer() {}

	static ImGuiContext* m_Context;

	ImGuiContext* ImGuiLayer::GetContext()
	{
		return m_Context;
	}

	void ImGuiLayer::OnAttach()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		m_Context = ImGui::CreateContext();
		ImGui::SetCurrentContext(m_Context);
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		DrayApp& app = DrayApp::Get();
		GLFWwindow* window = statc(GLFWwindow*, app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		DrayApp& app = DrayApp::Get();
		io.DisplaySize = ImVec2((f32)app.GetWindow().GetWidth(), (f32)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnImGuiRender()
	{

	}
}
