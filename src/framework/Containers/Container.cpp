#include "../pch.h"
#include "Container.h"

#include <iostream>

namespace ui 
{
	Container::Container(int posX, int posY, int width, int height, bool visibility)
		: Widget(posX, posY, width, height), m_visibility(visibility)
	{

	}

	InputEventState Container::ProcessInput( const InputEvent& event )
	{
		if (m_visibility) {
			for (auto& widget : m_widgets)
			{
				if (widget.first->ProcessInput(event) == InputEventState::Handled)
				{
					return InputEventState::Handled;
				}
			}
		}

		return InputEventState::Unhandled;
	}

	void Container::Draw(RenderContext& context) const
	{
		if (m_visibility) {
			for (auto& widget : m_widgets)
			{
				widget.first->Draw(context);
			}
		}
	}

	void Container::RecomputeGeometry() {
		for (auto& widget : m_widgets)
		{
			this->RepositionWidget(std::move(widget.first), widget.second);
		}
	}

	void Container::RepositionWidget(WidgetPtr&& widget, Anchor anchor) {
		if (anchor == Anchor::NONE) {
			// TODO: Add relative position

		} else if (anchor == Anchor::CENTER) {
			int centerX = (this->GetPosX() + this->GetWidth() / 2);
			widget->SetPosX((centerX - (widget->GetWidth() / 2)));

			int centerY = (this->GetPosY() + this->GetHeight() / 2);
			widget->SetPosY((centerY - (widget->GetHeight() / 2)));
		}
		else if (anchor == Anchor::TOP_CENTER) {
			int centerX = (this->GetPosX() + this->GetWidth() / 2);
			widget->SetPosX((centerX - (widget->GetWidth() / 2)));

			widget->SetPosY(0);
		}
		else if (anchor == Anchor::BOTTOM_CENTER) {
			int centerX = (this->GetPosX() + this->GetWidth() / 2);
			widget->SetPosX((centerX - (widget->GetWidth() / 2)));

			widget->SetPosY(this->GetHeight() - widget->GetHeight());
		}
		else if (anchor == Anchor::LEFT_CENTER) {
			widget->SetPosX(0);

			int centerY = (this->GetPosY() + this->GetHeight() / 2);
			widget->SetPosY((centerY - (widget->GetHeight() / 2)));
		}
		else if (anchor == Anchor::RIGHT_CENTER) {
			widget->SetPosX(this->GetWidth() - widget->GetWidth());

			int centerY = (this->GetPosY() + this->GetHeight() / 2);
			widget->SetPosY((centerY - (widget->GetHeight() / 2)));
		}
	}

	void Container::AddWidget(WidgetPtr&& widget, Anchor anchor)
	{
		this->RepositionWidget(std::move(widget), anchor);
		m_widgets.push_back(std::pair<WidgetPtr, Anchor>(std::move(widget), anchor));
	}

	void Container::SetVisibility(bool visibility) {
		m_visibility = visibility;
	}

	bool Container::GetVisibility() const {
		return m_visibility;
	}
}