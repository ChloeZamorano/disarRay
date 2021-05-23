#pragma once

#include "DrayIntern.h"

#include <glm/vec2.hpp>

namespace Dray
{
	class DRAY_API Input
	{
	public:
		static bool GetKey(u32 keycode)
			{ return s_Instance->GetKeyImpl(keycode); }
		static bool GetMouseButton(u32 button)
			{ return s_Instance->GetMouseButtonImpl(button); }
		static f32 GetMouseXPos()
			{ return s_Instance->GetMousePosImpl().x; }
		static f32 GetMouseYPos()
			{ return s_Instance->GetMousePosImpl().y; }
		static glm::vec2 GetMousePos()
			{ return s_Instance->GetMousePosImpl(); }

		static bool MakePoller();
	
	protected:
		virtual bool GetKeyImpl(u32 k) = 0;
		virtual bool GetMouseButtonImpl(u32 b) = 0;
		virtual glm::vec2 GetMousePosImpl() = 0;
	
	private:
		static Input* s_Instance;
	};
}