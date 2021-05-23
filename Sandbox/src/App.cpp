#include <Dray.h>

#define IMGUI_IMPL_API
#include <imgui.h>

class ExampleLayer : public Dray::Layer
{
public:
	ExampleLayer() :
		Layer("Example") {}

	void OnAttach() override
	{
		ImGui::SetCurrentContext(Dray::ImGuiLayer::GetContext());
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Dray Debug Settings");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnUpdate() override
	{
		if (Dray::Input::GetKey(DRAY_KEY_SPACE))
			DRAY_TRACE("Input Poller: Space bar pressed!");
	}
};

class Sandbox : public Dray::DrayApp
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}
};

Dray::DrayApp* Dray::MakeDrayApp()
{
	return new Sandbox();
}