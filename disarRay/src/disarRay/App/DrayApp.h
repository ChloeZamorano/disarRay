#pragma once

#include "DrayIntern.h"

#include "Window.h"
#include "ImGui/ImGuiLayer.h"
#include "Layers/LayerStack.h"
#include "Events/AppEvent.h"

namespace Dray
{
	class DRAY_API DrayApp
	{
	public:
		DrayApp();
		virtual ~DrayApp();


		void Run();


		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);


		inline Window& GetWindow() { return *m_Window; }

		static inline DrayApp& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);


		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;


		static DrayApp* s_Instance;
	};

	DrayApp* MakeDrayApp();
}
