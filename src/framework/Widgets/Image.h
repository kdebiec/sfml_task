#pragma once
#include "..\widget.h"
#include "..\pch.h"

namespace ui
{
	class Image : public Widget
	{
	public:
		Image(int posX, int posY, int width, int height, std::string imagePath = "");
		InputEventState ProcessInput(const InputEvent& event) override;
		void Draw(RenderContext& context) const override;

		void SetColor(const sf::Color& color);

	private:
		void RecomputeGeometry() override;

		sf::Vertex         	m_vertices[4];
		const sf::Texture* 	m_texture;
		sf::Sprite 			sprite;
	};
}
