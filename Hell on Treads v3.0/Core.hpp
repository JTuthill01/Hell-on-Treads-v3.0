#pragma once
#include <MainMenu/MainMenu.hpp>
#include <Entities/Enemy.hpp>
#include <HUD/HUD.hpp>
#include <Map Loader/MapLoader.hpp>

class Core
{
public:

	Core();
	~Core();

	void run();

private:
	void update(float& deltaTime);
	void processEvents();
	void startClock();
	void render(sf::RenderTarget& target);

	sf::RenderWindow mWindow;
	sf::Clock mDeltaTimeClock;
	sf::Event e;

	float mDeltaTime;

	std::unique_ptr<MainMenu> mMainMenu;
	Player mPlayer;
	Enemy mEnemy;
	HUD mHUD;
	MapLoader map;
};

