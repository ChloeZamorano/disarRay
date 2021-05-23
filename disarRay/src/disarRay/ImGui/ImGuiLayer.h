#pragma once

#include "DrayIntern.h"

#include "Layers/Layer.h"
#include "Events/AppEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "imgui.h"

namespace Dray 
{
	class DRAY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		static ImGuiContext* GetContext();

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}