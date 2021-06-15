#pragma once

class Inventory {
public:
	void SetChosenItem(int num) {m_chosen_item = num;}
	int  GetChosenItem() {return m_chosen_item;}

private:
	int m_chosen_item = 0;
};

namespace ui
{
	class Window;
}

class Application final
{
public:
	Application();
	~Application();

	void Initialize();
	void Run();

	ui::Window* GetMainWindow() const;
	const std::string& GetDataPath() const;

private:
	void SetDataPath( const char* dataPath );

	std::string m_dataPath;

	std::shared_ptr< ui::Window > m_mainWindow;
	std::shared_ptr< RenderContext > m_renderContext;
};
