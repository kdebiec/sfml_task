#include "Image.h"

#include <iostream>

namespace ui
{
	Image::Image(int posX, int posY, int width, int height, std::string imagePath)
		: Widget(posX, posY, width, height), m_texture(nullptr)
	{
		sf::Texture* texture = new sf::Texture();
		if (!texture->loadFromFile(imagePath))
			std::cout << "Couldnt load texture" << std::endl;
		else {
			m_texture = texture;
			texture->setSmooth(true);
			sprite.setTexture(*texture, true);
			sprite.setPosition(Vector2f((float)posX, (float)posY));
		}
	}

	InputEventState Image::ProcessInput(const InputEvent& event)
	{
		return InputEventState::Unhandled;
	}

	void Image::Draw(RenderContext& context) const
	{
		context.draw(sprite);
	}

	void Image::SetColor(const sf::Color& color)
	{
		sprite.setColor(color);
	}

	void Image::RecomputeGeometry()
	{
		int posX   = this->GetPosX();
		int posY   = this->GetPosY();
		int height = this->GetHeight();
		int width  = this->GetWidth();
		sprite.setPosition(sf::Vector2f((float)posX, (float)posY));
		sprite.setTextureRect(sf::Rect(sf::Vector2(0, 0), sf::Vector2(width, height)));
	}
}