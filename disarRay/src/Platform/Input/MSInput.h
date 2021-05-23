#pragma once

#include "Input.h"

namespace Dray
{
	class DRAY_API MSInput : public Input
	{
	protected:
		bool GetKeyImpl(u32 keycode) override;
		bool GetMouseButtonImpl(u32 button) override;
		glm::vec2 GetMousePosImpl() override;
	};
}
