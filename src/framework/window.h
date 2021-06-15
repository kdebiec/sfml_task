#pragma once

#include "widget.h"
#include <functional>

namespace ui
{	
	class Window final
	{
	public:
		Window();
		~Window();
		
		void ProcessInput( const InputEvent& event );
		void Draw( RenderContext& context ) const;

		void AddWidget(WidgetPtr&& widget);
		std::function<void(sf::Event::KeyEvent)> OnKeyPressed;
		
	private:
		std::vector< WidgetPtr > m_widgets;
	};
}
