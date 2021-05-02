#pragma once

#include "DrayIntern.h"

namespace Dray
{
	class DRAY_API DrayApp
	{
	public:
		DrayApp();
		virtual ~DrayApp();

		void Run();
	};

	DrayApp* MakeDrayApp();
}
