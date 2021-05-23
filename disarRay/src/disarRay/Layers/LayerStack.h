#pragma once

#include "DrayIntern.h"
#include "Layer.h"
#include <vector>

namespace Dray
{
	class DRAY_API LayerStack
	{
	public:
		typedef std::vector<Layer*> Stack;
		typedef std::vector<Layer*>::iterator StackIt;

		LayerStack	();
		~LayerStack	();

		void PushLayer	(Layer* layer);
		void PopLayer	(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay	(Layer* overlay);

		StackIt begin	() { return m_Layers.begin(); }
		StackIt end		() { return m_Layers.end(); }

	private:
		Stack	m_Layers;
		u32 m_LayerInsertIndex = 0;
	};
}
