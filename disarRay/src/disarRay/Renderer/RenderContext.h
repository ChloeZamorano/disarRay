#pragma once

#include "DrayIntern.h"

namespace Dray
{
	class DRAY_API RenderContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
