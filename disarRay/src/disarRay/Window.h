#pragma once

#include "drpch.h"

#include "DrayIntern.h"
#include "Events/Event.h"
#include "Layers/LayerStack.h"

namespace Dray
{
	struct WindowProps
	{
		str8 Title;
		u32 Width, Height;

		WindowProps(str8 title = "disarRay Engine",
			u32 width = 1080, u32 height = 720) :
			Title(title), Width(width), Height(height) {}
	};

	class DRAY_API Window
	{
	public:
		Window() {}
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void RenderStage1() = 0;
		virtual void RenderStage2() = 0;

		virtual u32 GetWidth() const = 0;
		virtual u32 GetHeight() const = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;


		static Window* Create(const WindowProps& data = WindowProps());
	};
}
