#pragma once
#include "..\widget.h"
#include "Image.h"
#include "TextLabel.h"
#include <functional>

namespace ui
{
	class Button : public Widget
	{
	public:
		Button(	int posX, int posY,
				int width, int height,
				std::string text, std::string imagePath, std::string fontPath
		);
		InputEventState ProcessInput(const InputEvent& event) override;
		void Draw(RenderContext& context) const override;

		void SetText(std::string text) {}
		void SetImage(std::string imagePath) {}

		void SetColor(const sf::Color& color);
		std::function<void()> OnHoverIn;
		std::function<void()> OnHoverOut;
		std::function<void()> OnClicked;

	private:
		void RecomputeGeometry() override;
		std::unique_ptr<Image> image;
		std::unique_ptr<TextLabel> textLabel;
		bool isHover;
	};
}
