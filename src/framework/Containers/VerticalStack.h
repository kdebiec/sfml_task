#pragma once
#include <vector>
#include "..\pch.h"
#include "stack.h"

namespace ui
{
	class VerticalStack : public Stack
	{
	public:
		VerticalStack(int posX, int posY, int width, int height, int spacing);
		virtual void AddWidget(WidgetPtr&& widget) override;
		void RecomputeGeometry() override;

	private:
		void RepositionWidget(WidgetPtr&& widget);

		int m_posy_of_last_element;
	};
}
