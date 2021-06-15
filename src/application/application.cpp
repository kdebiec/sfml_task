#include "pch.h"
#include "../framework/window.h"
#include "application.h"

#include "../framework/containers/Container.h"
#include "../framework/Widgets/Button.h"

#include "../framework/StyleLoader.h"

const auto BUTTON_COLOR = sf::Color(255, 255, 255, 255);
const auto BUTTON_HOVERED_COLOR = sf::Color(255, 255, 255, 128);

Application::Application() = default;
Application::~Application() = default;

void Application::Initialize()
{
	m_renderContext = std::make_shared<RenderContext>( sf::VideoMode( 1920, 1080 ), "Recruitment task");

	SetDataPath( "../../data/" );

	StyleLoader styleLoader;
	if (!styleLoader.loadDocument(GetDataPath() + "game_ui.json")) {
		m_renderContext->close();
	}
	styleLoader.SetViewportWidth(m_renderContext->getSize().x);
	styleLoader.SetViewportHeight(m_renderContext->getSize().y);

	if( m_mainWindow = std::make_shared<ui::Window>() )
	{
		std::map<std::string, std::shared_ptr<ui::Widget>> widgets = styleLoader.createTree(m_mainWindow);

		// ==========================================================
		// ======================= MENU SCREEN =======================

		//// ========================== RESUME BUTTON =======================
		auto resumeButton = std::reinterpret_pointer_cast<ui::Button>(widgets["resumeButton"]);
		resumeButton->OnClicked = [menuScreen = std::reinterpret_pointer_cast<ui::Container>(widgets["menuScreen"])]() {
			menuScreen->SetVisibility(false);
		};
		resumeButton->OnHoverIn = [button = resumeButton]() {
			button->SetColor(BUTTON_HOVERED_COLOR);
		};
		resumeButton->OnHoverOut = [button = resumeButton]() {
			button->SetColor(BUTTON_COLOR);
		};

		//// ========================== SETTINGS BUTTON =======================
		auto settingsButton = std::reinterpret_pointer_cast<ui::Button>(widgets["settingsButton"]);
		settingsButton->OnHoverIn = [button = settingsButton]() {
			button->SetColor(BUTTON_HOVERED_COLOR);
		};
		settingsButton->OnHoverOut = [button = settingsButton]() {
			button->SetColor(BUTTON_COLOR);
		};

		//// ========================== EXIT BUTTON =======================
		auto exitButton = std::reinterpret_pointer_cast<ui::Button>(widgets["exitButton"]);
		exitButton->OnClicked = [ptr = m_renderContext]() {
			ptr->close();
		};
		exitButton->OnHoverIn = [button = exitButton]() {
			button->SetColor(BUTTON_HOVERED_COLOR);
		};
		exitButton->OnHoverOut = [button = exitButton]() {
			button->SetColor(BUTTON_COLOR);
		};

		//// ==========================================================
		//// ======================= HUD SCREEN =======================

		std::vector<int> a;
		auto buttons = std::make_shared<std::vector<std::shared_ptr<ui::Button>>>();
		buttons->push_back(std::reinterpret_pointer_cast<ui::Button>(widgets["item1Button"]));
		buttons->push_back(std::reinterpret_pointer_cast<ui::Button>(widgets["item2Button"]));
		buttons->push_back(std::reinterpret_pointer_cast<ui::Button>(widgets["item3Button"]));
		std::shared_ptr<int> chosenItem = std::make_shared<int>(-1);

		for (int i = 0; i < 3; i++) {
			auto button = (*buttons)[i];
			button->OnClicked = [index = i, buttons = buttons, chosenItem = chosenItem]() {
				(*chosenItem) = index;
				for (int i = 0; i < 3; i++) {
					auto button = (*buttons)[i];
					if (index == i) {
						button->SetColor(BUTTON_HOVERED_COLOR);
					}
					else {
						button->SetColor(BUTTON_COLOR);
					}
				}
			};
			button->OnHoverIn = [index = i, chosenItem = chosenItem, button = button]() {
				if (index != (*chosenItem)) {
					button->SetColor(BUTTON_HOVERED_COLOR);
				}
			};
			button->OnHoverOut = [index = i, chosenItem = chosenItem, button = button]() {
				if (index != (*chosenItem)) {
					button->SetColor(BUTTON_COLOR);
				}
			};
		}


		//// =========================================================
		//// ====================== Main Window ======================
		m_mainWindow->OnKeyPressed = [
			chosenItem = chosenItem,
			buttons = buttons,
			menuScreen = std::reinterpret_pointer_cast<ui::Container>(widgets["menuScreen"])
		](sf::Event::KeyEvent keyEvent) {
			if (keyEvent.code == sf::Keyboard::Escape) {
				menuScreen->SetVisibility(!menuScreen->GetVisibility());
			} else if (keyEvent.code == sf::Keyboard::Num1) {
				if ((*chosenItem) != -1) {
					(*buttons)[(*chosenItem)]->SetColor(BUTTON_COLOR);
				}
				(*chosenItem) = 0;
				(*buttons)[(*chosenItem)]->SetColor(BUTTON_HOVERED_COLOR);
			} else if (keyEvent.code == sf::Keyboard::Num2) {
				if ((*chosenItem) != -1) {
					(*buttons)[(*chosenItem)]->SetColor(BUTTON_COLOR);
				}
				(*chosenItem) = 1;
				(*buttons)[(*chosenItem)]->SetColor(BUTTON_HOVERED_COLOR);
			} else if (keyEvent.code == sf::Keyboard::Num3) {
				if ((*chosenItem) != -1) {
					(*buttons)[(*chosenItem)]->SetColor(BUTTON_COLOR);
				}
				(*chosenItem) = 2;
				(*buttons)[(*chosenItem)]->SetColor(BUTTON_HOVERED_COLOR);
			}
		};
	}
}

void Application::Run()
{
	while( m_renderContext->isOpen() )
	{
		InputEvent event;
		while( m_renderContext->pollEvent( event ) )
		{
			if( event.type == InputEvent::Closed )
			{
				m_renderContext->close();
			}
			else
			{
				m_mainWindow->ProcessInput( event );
			}
		}

		m_renderContext->clear();
		{
			m_mainWindow->Draw( *m_renderContext );
		}
		m_renderContext->display();
	}

}

ui::Window* Application::GetMainWindow() const
{
	return m_mainWindow.get();
}

const std::string& Application::GetDataPath() const
{
	return m_dataPath;
}

void Application::SetDataPath( const char* dataPath )
{
	m_dataPath = dataPath;
}

