#include "drpch.h"
#include "DrayApp.h"

#include <glad/glad.h>

namespace Dray
{
	DrayApp* DrayApp::s_Instance = nullptr;

	DrayApp::DrayApp()
	{
		DRAY_ENGINE_ASSERT(!s_Instance,
			"DrayApp is a singleton, cannot have more than one per instance!",
			"DrayApp singleton verified, creating new DrayApp now!")
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(DRAY_BIND_FN(DrayApp::OnEvent));
	}

	DrayApp::~DrayApp() {}

	void DrayApp::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void DrayApp::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void DrayApp::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(DRAY_BIND_FN(DrayApp::OnWindowClose));

		for (LayerStack::StackIt it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
				break;
		}
	}

	const char* coomer[] =
	{
		"Hello, Gordon!",
		"I've been outside Black Mesa, Dr. Freeman. There's nothing there. But YOU. I know there's a world in your dreams. AND I NEED TO GO THERE!!! ",
		"Gordon? If you woke up one day, and realized everything around you was a lie...was FAKE...What would you do? ",
		"Look Gordon! Ropes! We can use these to help with large pits! ",
		"HELP ME GORDON! ",
		"Gordon...Every time you go to sleep I can feel my body TORN apart...ATOM by ATOM...It's agonizing Gordon...I've SEEN outside Black Mesa, Gordon...There's NOTHING...But I know YOU. There's a world outside here, Gordon. AND I NEED YOU TO TAKE ME THERE...",
		"I did have a wife, but they took her in the divorce. ",
		"You're not a war criminal if there's no more military to judge you. ",
		"Gordon, I'm tired. ",
		"Gordon, titty boob huge fuck. ",
		"He was my best friend...but he owed me seven dollars! "
	};

	void DrayApp::Run()
	{
		while (m_Running)
		{
			m_Window->RenderUpdate(m_LayerStack);
		}
	}

	bool DrayApp::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
