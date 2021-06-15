#pragma once
#include <vector>
#include "..\pch.h"
#include "..\widget.h"

namespace ui
{
	class Stack : public Widget
	{
	public:
		Stack(int posX, int posY, int width, int height, int spacing = 0);
		virtual InputEventState ProcessInput(const InputEvent& event) override;
		virtual void Draw(RenderContext& context) const override;

		virtual void AddWidget(WidgetPtr&& widget);
		virtual void RecomputeGeometry() = 0;

	protected:
		virtual void RepositionWidget(WidgetPtr&& widget) = 0;

		std::vector<WidgetPtr> m_widgets;
		int m_spacing;
	};
}
