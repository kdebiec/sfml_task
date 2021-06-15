#include "VerticalStack.h"
#include <iostream>

namespace ui
{
	VerticalStack::VerticalStack(int posX, int posY, int width, int height, int spacing)
		: Stack(posX, posY, width, height, spacing), m_posy_of_last_element(posY)
	{}

	void VerticalStack::RecomputeGeometry() {
		m_posy_of_last_element = this->GetPosY();
		for (auto& widget : m_widgets)
		{
			this->RepositionWidget(std::move(widget));
		}
	}

	void VerticalStack::RepositionWidget(WidgetPtr&& widget) {
		widget->SetPosY(m_posy_of_last_element);
		widget->SetPosX(this->GetPosX());
		m_posy_of_last_element += widget->GetHeight() + m_spacing;
	}

	void VerticalStack::AddWidget(WidgetPtr&& widget) {
		this->RepositionWidget(std::move(widget));
		this->SetHeight(this->GetHeight() + widget->GetHeight() + m_spacing);
		if (widget->GetWidth() > this->GetWidth()) {
			this->SetWidth(widget->GetWidth());
		}
		m_widgets.push_back(std::move(widget));
	}
}