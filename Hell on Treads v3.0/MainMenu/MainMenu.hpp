#pragma once
class MainMenu
{
public:
	MainMenu(sf::RenderWindow& window);
	~MainMenu();

	void render(sf::RenderTarget& target);
	void handleButtonEvents(sf::Event& e);

	void setIsClosed(bool t_f) { mIsClosed = t_f; }
	bool getIsClosed() { return mIsClosed; }

private:
	void setText(sf::RenderWindow& window);
	void initTextures();
	void gui(sf::RenderWindow& window);

	sf::RenderWindow mWindow;
	sf::Font mFont;
	sf::Text mText;

	sf::Texture mBackgroundTexture;
	sf::Sprite mBackgroundSprite;

	std::unique_ptr<tgui::Gui> mGui;

	bool mIsClosed;
};

