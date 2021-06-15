#include "TextLabel.h"
#include <iostream>

namespace ui
{
	TextLabel::TextLabel(int posX, int posY, int width, int height, std::string text, std::string fontPath)
		: Widget(posX, posY, width, height)
	{
		if (!font.loadFromFile(fontPath))
			std::cout << "Couldnt load font" << std::endl;

		m_text.setFont(font);
		m_text.setString(text);
		m_text.setCharacterSize(32);
		m_text.setFillColor(sf::Color::White);
		m_text.setStyle(sf::Text::Bold);
		//m_text.setPosition(sf::Vector2f((float)posX, (float)posY));
		sf::FloatRect textRect = m_text.getLocalBounds();
		m_text.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		m_text.setPosition(sf::Vector2f((float)posX + (width / 2.0f), (float)posY + (height/ 2.0f)));
	}

	InputEventState TextLabel::ProcessInput(const InputEvent& event)
	{
		return InputEventState::Handled;
	}

	void TextLabel::Draw(RenderContext& context) const
	{
		context.draw(m_text);
	}

	void TextLabel::RecomputeGeometry()
	{
		//m_text.setPosition(sf::Vector2f(1920 / 2.0f, 1080 / 2.0f));
		//m_text.setPosition(sf::Vector2f((float)this->GetPosX(), (float)this->GetPosY()));
		m_text.setPosition(sf::Vector2f((float)this->GetPosX() + (this->GetWidth() / 2.0f), (float)this->GetPosY() + (this->GetHeight() / 2.0f)));
	}
}