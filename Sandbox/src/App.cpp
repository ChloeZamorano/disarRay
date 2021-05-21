#include <Dray.h>

class Sandbox : public Dray::DrayApp
{
public:
	Sandbox()
	{
		PushOverlay(new Dray::ImGuiLayer());
	}

	~Sandbox() {}
};

Dray::DrayApp* Dray::MakeDrayApp()
{
	return new Sandbox();
}
