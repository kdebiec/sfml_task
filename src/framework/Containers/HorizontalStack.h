#pragma once
#include <vector>
#include "..\pch.h"
#include "stack.h"

namespace ui
{
	class HorizontalStack : public Stack
	{
	public:
		HorizontalStack(int posX, int posY, int width, int height, int spacing = 0);
		virtual void AddWidget(WidgetPtr&& widget) override;
		void RecomputeGeometry() override;

	private:
		void RepositionWidget(WidgetPtr&& widget);

		int m_posx_of_last_element;
	};
}
