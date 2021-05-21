#pragma once

#include <GLFW/glfw3.h>

#include "Window.h"

namespace Dray
{
	class MSWindow : public Window
	{
	public:
		MSWindow(const WindowProps& data);
		~MSWindow();

		void RenderUpdate(LayerStack& stack) override;

		inline u32 GetWidth() const override { return m_Data.Width; }
		inline u32 GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		
		void* GetGLFWWindow() const override { return reinterpret_cast<void*>(m_Window); }

	private:
		virtual void Init(const WindowProps& data);
		virtual void Shutdown();

		struct WindowData
		{
			str8 Title;
			u32 Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		GLFWwindow* m_Window;

		WindowData m_Data;
	};
}
