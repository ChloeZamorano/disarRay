#pragma once

#include "DrayIntern.h"

namespace Dray
{
	class DRAY_API RasterContext
	{
	public:
		virtual void Init() = 0;
		virtual void ClearColor(f32 r, f32 g, f32 b, f32 a) = 0; // TODO: Move this to rasterizer class.
		virtual void SwapBuffers() = 0;
	};
}
