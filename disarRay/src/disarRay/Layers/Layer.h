#pragma once

#include "DrayIntern.h"
#include "Events/Event.h"

namespace Dray
{
	class DRAY_API Layer
	{
	public:
		Layer(const str8& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}

		inline const str8& GetName() const { return m_DebugName; }

	protected:
		str8 m_DebugName;
	};
}
