#include "..\pch.h"
#include "Button.h"
#include <iostream>

namespace ui 
{
	Button::Button(	int posX, int posY, int width, int height, 
					std::string text, std::string imagePath, 
					std::string fontPath)
		: Widget(posX, posY, width, height), isHover(false)
	{
		image = std::make_unique<Image>(posX, posY, width, height, imagePath);
		textLabel = std::make_unique<TextLabel>(posX, posY, width, height, text, fontPath);
		
		OnHoverIn  = []() {};
		OnHoverOut = []() {};
		OnClicked  = []() {};
	}

	InputEventState Button::ProcessInput(const InputEvent& event)
	{
		if (event.mouseMove.x > this->GetPosX()
			&& event.mouseMove.x < this->GetPosX() + this->GetWidth()
			&& event.mouseMove.y > this->GetPosY()
			&& event.mouseMove.y < this->GetPosY() + this->GetHeight())
		{
			if (!isHover) {
				OnHoverIn();
				isHover = true;
			}
		}
		else {
			if (isHover) {
				OnHoverOut();
			}
			isHover = false;
		}

		if (event.mouseButton.button == sf::Mouse::Button::Left
			&& event.mouseButton.x > this->GetPosX()
			&& event.mouseButton.x < this->GetPosX() + this->GetWidth()
			&& event.mouseButton.y > this->GetPosY()
			&& event.mouseButton.y < this->GetPosY() + this->GetHeight())
		{
			OnClicked();
			return InputEventState::Handled;
		}

		return InputEventState::Unhandled;
	}

	void Button::Draw(RenderContext& context) const
	{
		image->Draw(context);
		textLabel->Draw(context);
	}

	void Button::SetColor(const sf::Color& color) {
		image->SetColor(color);
	}

	void Button::RecomputeGeometry() {
		image->SetPosX(this->GetPosX());
		image->SetPosY(this->GetPosY());
		image->SetHeight(this->GetHeight());
		image->SetWidth(this->GetWidth());

		textLabel->SetPosX(this->GetPosX());
		textLabel->SetPosY(this->GetPosY());
		textLabel->SetHeight(this->GetHeight());
		textLabel->SetWidth(this->GetWidth());
	}
}