#include "Stack.h"

namespace ui
{
	Stack::Stack(int posX, int posY, int width, int height, int spacing)
		: Widget(posX, posY, width, height), m_spacing(spacing)
	{

	}

	InputEventState Stack::ProcessInput(const InputEvent& event)
	{
		for (auto& widget : m_widgets)
		{
			if (widget->ProcessInput(event) == InputEventState::Handled)
			{
				return InputEventState::Handled;
			}
		}

		return InputEventState::Unhandled;
	}

	void Stack::Draw(RenderContext& context) const
	{
		for (auto& widget : m_widgets)
		{
			widget->Draw(context);
		}
	}

	void Stack::AddWidget(WidgetPtr&& widget)
	{
		this->RepositionWidget(std::move(widget));
		m_widgets.push_back(std::move(widget));
	}
}