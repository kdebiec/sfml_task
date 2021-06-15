#pragma once
#include <vector>
#include "..\Widget.h"
#include "..\pch.h"

namespace ui {
	class Container: public Widget
	{
	public:
		enum Anchor {
			NONE,
			TOP_CENTER,
			BOTTOM_CENTER,
			LEFT_CENTER,
			RIGHT_CENTER,
			CENTER
		};

		Container(int posX, int posY, int width, int height, bool visibility = true);
		virtual InputEventState ProcessInput(const InputEvent& event) override;
		virtual void Draw(RenderContext& context) const override;

		void AddWidget(WidgetPtr&& widget, Anchor anchor = Anchor::NONE);
		void SetVisibility(bool visibility);
		bool GetVisibility() const;

		void RecomputeGeometry() override;

	private:
		void RepositionWidget(WidgetPtr&& widget, Anchor anchor);

		std::vector<std::pair<WidgetPtr, Anchor>> m_widgets;
		bool m_visibility;
	};
}

