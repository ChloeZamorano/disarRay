#pragma once

#include "DrayIntern.h"
#include "Layers/Layer.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Events/AppEvent.h"

namespace Dray
{
	class DRAY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);

	private:
		bool OnMouseButtonDown(MouseButtonDownEvent& e);
		bool OnMouseButtonUp(MouseButtonUpEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnKeyDown(KeyDownEvent& e);
		bool OnKeyUp(KeyUpEvent& e);
		bool OnKeyTyped(KeyTypedEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

		f32 m_Time = 0.0f;
	};
}
