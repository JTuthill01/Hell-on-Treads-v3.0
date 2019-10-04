#include "pch.hpp"
#include "MainMenu.hpp"

MainMenu::MainMenu(sf::RenderWindow & window)
{
	mGui = std::make_unique<tgui::Gui>();

	mGui->setTarget(window);

	gui(window);

	setText(window);

	initTextures();
}

MainMenu::~MainMenu() = default;

void MainMenu::render(sf::RenderTarget& target)
{
	if (!mIsClosed)
	{
		target.draw(mBackgroundSprite);

		target.draw(mText);

		mGui->draw();
	}
}

void MainMenu::handleButtonEvents(sf::Event& e) { mGui->handleEvent(e); }

void MainMenu::setText(sf::RenderWindow & window)
{
	if (!mFont.loadFromFile("Resources/Fonts/Anton-Regular.ttf"))
		std::cerr << "Font failed to load \n";

	mText.setFillColor(sf::Color(255, 255, 255, 190));
	mText.setCharacterSize(100U);
	mText.setFont(mFont);
	mText.setString("Hell on Treads v3.0");
	mText.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2 - 450, static_cast<float>(window.getSize().y) - 800.F));
}

void MainMenu::initTextures()
{
	if (!mBackgroundTexture.loadFromFile("Resources/Menu/tank.png"))
		std::cerr << "";

	mBackgroundSprite.setTexture(mBackgroundTexture);
}

void MainMenu::gui(sf::RenderWindow & window)
{
	tgui::Theme theme{ "Resources/themes/black.txt" };

	auto mButtons = tgui::Button::create();
	mButtons->setPosition(400, 600);
	mButtons->setRenderer(theme.getRenderer("Button"));
	mButtons->setText("Play");
	mButtons->setTextSize(25U);
	mButtons->setSize(150, 50);
	mButtons->connect("pressed", [&]() { mIsClosed = true; });
	mGui->add(mButtons);

	auto mButton = tgui::Button::create();
	mButton->setPosition(400, 700);
	mButton->setRenderer(theme.getRenderer("Button"));
	mButton->setText("Quit");
	mButton->setTextSize(25U);
	mButton->setSize(150, 50);
	mButton->connect("pressed", [&]() { window.close(); });
	mGui->add(mButton);
}
