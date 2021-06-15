#pragma once

#include <string>
#include "pch.h"
#include <map>
#include "Widget.h"
#include "Window.h"

class StyleLoader
{
public:
	StyleLoader();
	bool loadDocument(std::string path);
	std::map<std::string, std::shared_ptr<ui::Widget>>& createTree(std::shared_ptr<ui::Window> window);
	std::shared_ptr<ui::Widget> getElementById(std::string path);

	void SetViewportWidth(int viewportWidth);
	void SetViewportHeight(int viewportHeight);

private:
	enum WidgetType {
		WINDOW,
		CONTAINER,
		STACK
	};
	void CreateChild(
		const Json::Value& val,
		const std::shared_ptr<ui::Widget> parent,
		WidgetType widgetType
	);
	int GetWidthFromJsonValue(const Json::Value &val);
	int GetHeightFromJsonValue(const Json::Value &val);

	Json::Document m_json_document;
	std::map<std::string, std::shared_ptr<ui::Widget>> m_widgets;

	int m_viewport_width;
	int m_viewport_height;
};

