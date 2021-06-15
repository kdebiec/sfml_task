#pragma once
#include "..\widget.h"
#include "..\pch.h"

namespace ui
{
	class TextLabel : public Widget
	{
	public:
		TextLabel(int posX, int posY, int width, int height, std::string text, std::string fontPath);
		InputEventState ProcessInput(const InputEvent& event) override;
		virtual void Draw(RenderContext& context) const override;
	
	private:
		void RecomputeGeometry() override;
		sf::Font font;
		sf::Text m_text;
	};
}
