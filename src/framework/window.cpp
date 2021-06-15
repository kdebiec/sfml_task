#include "pch.h"
#include "window.h"

namespace ui
{
	Window::Window() {
		OnKeyPressed = [](sf::Event::KeyEvent) {};
	}

	Window::~Window() = default;

	void Window::ProcessInput( const InputEvent& event )
	{
		if (event.type == sf::Event::EventType::KeyPressed) {
			OnKeyPressed(event.key);
		}

		for( auto& widget : m_widgets )
		{
			if( widget->ProcessInput( event ) == InputEventState::Handled )
			{
				return;
			}
		}
	}

	void Window::Draw( RenderContext& context ) const
	{
		for( auto& widget : m_widgets )
		{
			widget->Draw( context );
		}
	}

	void Window::AddWidget( WidgetPtr&& widget )
	{
		m_widgets.push_back( std::move( widget ) );
	}

}
