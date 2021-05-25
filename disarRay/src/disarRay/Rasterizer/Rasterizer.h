#pragma once

#include "DrayIntern.h"

namespace Dray
{
	enum class RasterizerAPI
	{
		None = 0,
		OpenGL = 1,
		DirectX11 = 2,
		DirectX12 = 3,
		Vulkan = 4,
		Metal = 5,
	};

	class DRAY_API Rasterizer
	{
	public:
		inline static RasterizerAPI GetAPI() { return s_RasterizerAPI; }

	private:
		static RasterizerAPI s_RasterizerAPI;
	};
}
