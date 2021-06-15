#include "HorizontalStack.h"
#include <iostream>

namespace ui
{
	HorizontalStack::HorizontalStack(int posX, int posY, int width, int height, int spacing)
		: Stack(posX, posY, width, height, spacing), m_posx_of_last_element(posX)
	{

	}

	void HorizontalStack::RecomputeGeometry() {
		m_posx_of_last_element = this->GetPosX();

		for (auto& widget : m_widgets)
		{
			this->RepositionWidget(std::move(widget));
		}
	}

	void HorizontalStack::RepositionWidget(WidgetPtr&& widget) {
		widget->SetPosX(m_posx_of_last_element);
		widget->SetPosY(this->GetPosY());
		m_posx_of_last_element += widget->GetWidth() + m_spacing;
	}

	void HorizontalStack::AddWidget(WidgetPtr&& widget) {
		this->RepositionWidget(std::move(widget));
		this->SetWidth(this->GetWidth() + widget->GetWidth() + m_spacing);
		if (widget->GetHeight() > this->GetHeight()) {
			this->SetHeight(widget->GetHeight());
		}
		m_widgets.push_back(std::move(widget));
	}
}