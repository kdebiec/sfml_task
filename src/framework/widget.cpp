#include "pch.h"
#include "widget.h"

namespace ui
{
	Widget::Widget(int posX, int posY, int width, int height)
		: m_posX(posX)
		, m_posY(posY)
		, m_width(width)
		, m_height(height)
	{
	}

	Widget::~Widget() = default;

	void Widget::SetPosX(int posX) 
	{ 
		this->m_posX = posX;
		this->RecomputeGeometry();
	}
	
	void Widget::SetPosY(int posY) 
	{ 
		this->m_posY = posY; 
		this->RecomputeGeometry();
	}

	void Widget::SetWidth(int width) 
	{ 
		this->m_width = width; 
		this->RecomputeGeometry();
	}

	void Widget::SetHeight(int height) 
	{ 
		this->m_height = height; 
		this->RecomputeGeometry();
	}

	int Widget::GetPosX() const
	{
		return m_posX;
	}

	int Widget::GetPosY() const
	{
		return m_posY;
	}

	int Widget::GetWidth() const
	{
		return m_width;
	}

	int Widget::GetHeight() const
	{
		return m_height;
	}


}
