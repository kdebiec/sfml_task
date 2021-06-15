#include "pch.h"
#include "StyleLoader.h"

#include <iostream>
#include <rapidjson/istreamwrapper.h>

#include "./Containers/Container.h"
#include "./Containers/VerticalStack.h"
#include "./Containers/HorizontalStack.h"
#include "./Widgets/TextLabel.h"
#include "./Widgets/Button.h"
#include "./Widgets/Image.h"


StyleLoader::StyleLoader() = default;

bool StyleLoader::loadDocument(std::string path) {
	std::ifstream ifs{ path };
	if (!ifs.is_open())
	{
		std::cerr << "Could not open file for reading!\n";
		return false;
	}

	Json::IStreamWrapper isw{ ifs };
	m_json_document.ParseStream(isw);

	return true;
}

void StyleLoader::SetViewportWidth(int viewportWidth) {
	m_viewport_width = viewportWidth;
}

void StyleLoader::SetViewportHeight(int viewportHeight) {
	m_viewport_height = viewportHeight;
}

std::map<std::string, std::shared_ptr<ui::Widget>>& StyleLoader::createTree(std::shared_ptr<ui::Window> window) {
	const Json::Value& children = m_json_document["children"];
	if (children.IsArray()) {
		for (Json::SizeType i = 0; i < children.Size(); i++)
			CreateChild(children[i], std::reinterpret_pointer_cast<ui::Widget>(window), WidgetType::WINDOW);
	}

	return m_widgets;
}

ui::Container::Anchor getAnchorFromString(std::string anchorName) {
	if (anchorName == "TOP_CENTER") {
		return ui::Container::Anchor::TOP_CENTER;
	}
	else if (anchorName == "BOTTOM_CENTER") {
		return ui::Container::Anchor::BOTTOM_CENTER;
	}
	else if (anchorName == "LEFT_CENTER") {
		return ui::Container::Anchor::LEFT_CENTER;
	}
	else if (anchorName == "RIGHT_CENTER") {
		return ui::Container::Anchor::RIGHT_CENTER;
	}
	else if (anchorName == "CENTER") {
		return ui::Container::Anchor::CENTER;
	}

	return ui::Container::Anchor::NONE;
}

int StyleLoader::GetWidthFromJsonValue(const Json::Value &val) {
	int width = val["width"].GetInt();
	if (width == -1) {
		return m_viewport_width;
	}
	else if (width > -1) {
		return width;
	}

	return 0;
}

int StyleLoader::GetHeightFromJsonValue(const Json::Value &val) {
	int height = val["height"].GetInt();
	if (height == -1) {
		return m_viewport_height;
	}
	else if (height > -1) {
		return height;
	}

	return 0;
}

// TODO Image color loading
void StyleLoader::CreateChild(
	const Json::Value& val,
	const std::shared_ptr<ui::Widget> parent,
	WidgetType widgetType
) {
	std::string type = val["type"].GetString();

	if (type == "Container") {
		int x = val["x"].GetInt();
		int y = val["y"].GetInt();
		int width = GetWidthFromJsonValue(val);
		int height = GetHeightFromJsonValue(val);
		bool visibility = val["visibility"].GetBool();

		std::shared_ptr<ui::Container> container = std::make_shared<ui::Container>(
			x, y, width, height, visibility
		);

		const Json::Value& children = val["children"];
		if (children.IsArray()) {
			for (Json::SizeType i = 0; i < children.Size(); i++)
				CreateChild(children[i], container, WidgetType::CONTAINER);
		}

		std::shared_ptr<ui::Widget> container2(container);

		if (widgetType == WidgetType::WINDOW) {
			std::reinterpret_pointer_cast<ui::Window>(parent)->AddWidget(std::move(container));
		}
		else if (widgetType == WidgetType::CONTAINER) {
			ui::Container::Anchor anchor = getAnchorFromString(val["anchor"].GetString());
			std::reinterpret_pointer_cast<ui::Container>(parent)->AddWidget(std::move(container), anchor);
		}
		else if (widgetType == WidgetType::STACK) {
			std::reinterpret_pointer_cast<ui::Stack>(parent)->AddWidget(std::move(container));
		}

		m_widgets[val["id"].GetString()] = container2;
	}
	else if (type == "HorizontalStack") {
		int x = val["x"].GetInt();
		int y = val["y"].GetInt();
		int width = GetWidthFromJsonValue(val);
		int height = GetHeightFromJsonValue(val);
		int spacing = val["spacing"].GetInt();

		std::shared_ptr<ui::Widget> hStack = std::make_shared<ui::HorizontalStack>(
			x, y, width, height, spacing
		);

		const Json::Value& children = val["children"];
		if (children.IsArray()) {
			for (Json::SizeType i = 0; i < children.Size(); i++)
				CreateChild(children[i], hStack, WidgetType::STACK);
		}

		std::shared_ptr<ui::Widget> hStack2(hStack);

		if (widgetType == WidgetType::WINDOW) {
			std::reinterpret_pointer_cast<ui::Window>(parent)->AddWidget(std::move(hStack));
		}
		else if (widgetType == WidgetType::CONTAINER) {
			ui::Container::Anchor anchor = getAnchorFromString(val["anchor"].GetString());
			std::reinterpret_pointer_cast<ui::Container>(parent)->AddWidget(std::move(hStack), anchor);
		}
		else if (widgetType == WidgetType::STACK) {
			std::reinterpret_pointer_cast<ui::Stack>(parent)->AddWidget(std::move(hStack));
		}


		m_widgets[val["id"].GetString()] = hStack2;
	}
	else if (type == "VerticalStack") {
		int x = val["x"].GetInt();
		int y = val["y"].GetInt();
		int width = GetWidthFromJsonValue(val);
		int height = GetHeightFromJsonValue(val);
		int spacing = val["spacing"].GetInt();

		std::shared_ptr<ui::Widget> vStack = std::make_shared<ui::VerticalStack>(
			x, y, width, height, spacing
		);

		const Json::Value& children = val["children"];
		if (children.IsArray()) {
			for (Json::SizeType i = 0; i < children.Size(); i++)
				CreateChild(children[i], vStack, WidgetType::STACK);
		}

		std::shared_ptr<ui::Widget> vStack2(vStack);

		if (widgetType == WidgetType::WINDOW) {
			std::reinterpret_pointer_cast<ui::Window>(parent)->AddWidget(std::move(vStack));
		}
		else if (widgetType == WidgetType::CONTAINER) {
			ui::Container::Anchor anchor = getAnchorFromString(val["anchor"].GetString());
			std::reinterpret_pointer_cast<ui::Container>(parent)->AddWidget(std::move(vStack), anchor);
		}
		else if (widgetType == WidgetType::STACK) {
			std::reinterpret_pointer_cast<ui::Stack>(parent)->AddWidget(std::move(vStack));
		}

		m_widgets[val["id"].GetString()] = vStack2;
	}
	else if (type == "Image") {
		int x = val["x"].GetInt();
		int y = val["y"].GetInt();
		int width = GetWidthFromJsonValue(val);
		int height = GetHeightFromJsonValue(val);
		std::string color = val["color"].GetString();

		std::shared_ptr<ui::Widget> image = std::make_shared<ui::Image>(
			x, y, width, height
		);

		std::shared_ptr<ui::Widget> image2(image);

		if (widgetType == WidgetType::WINDOW) {
			std::reinterpret_pointer_cast<ui::Window>(parent)->AddWidget(std::move(image));
		}
		else if (widgetType == WidgetType::CONTAINER) {
			ui::Container::Anchor anchor = getAnchorFromString(val["anchor"].GetString());
			std::reinterpret_pointer_cast<ui::Container>(parent)->AddWidget(std::move(image), anchor);
		}
		else if (widgetType == WidgetType::STACK) {
			std::reinterpret_pointer_cast<ui::Stack>(parent)->AddWidget(std::move(image));
		}

		m_widgets[val["id"].GetString()] = image2;
	}
	else if (type == "Button") {
		int x = val["x"].GetInt();
		int y = val["y"].GetInt();
		int width = GetWidthFromJsonValue(val);
		int height = GetHeightFromJsonValue(val);
		std::string text = val["text"].GetString();
		std::string image = val["image"].GetString();
		std::string font = val["font"].GetString();

		std::shared_ptr<ui::Widget> button = std::make_shared<ui::Button>(
			x, y, width, height, text, image, font
		);

		std::shared_ptr<ui::Widget> button2(button);

		if (widgetType == WidgetType::WINDOW) {
			std::reinterpret_pointer_cast<ui::Window>(parent)->AddWidget(std::move(button));
		}
		else if (widgetType == WidgetType::CONTAINER) {
			ui::Container::Anchor anchor = getAnchorFromString(val["anchor"].GetString());
			std::reinterpret_pointer_cast<ui::Container>(parent)->AddWidget(std::move(button), anchor);
		}
		else if (widgetType == WidgetType::STACK) {
			std::reinterpret_pointer_cast<ui::Stack>(parent)->AddWidget(std::move(button));
		}

		m_widgets[val["id"].GetString()] = button2;
	}
}
