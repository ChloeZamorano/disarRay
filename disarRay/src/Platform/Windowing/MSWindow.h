#pragma once

#include <GLFW/glfw3.h>
#include "Window.h"
#include "Rasterizer/RasterContext.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Dray
{
	class MSWindow : public Window
	{
	public:
		MSWindow(const WindowProps& data);
		~MSWindow();

		void RenderStage1() override;
		void RenderStage2() override;

		inline u32 GetWidth() const override { return m_Data.Width; }
		inline u32 GetHeight() const override { return m_Data.Height; }

		void* GetNativeWindow() const override { return m_Window; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

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
		RasterContext* m_Context;

		WindowData m_Data;
	};
}
