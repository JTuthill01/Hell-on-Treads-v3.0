#include "pch.hpp"
#include "Core.hpp"

Core::Core() : mDeltaTime(0.F)
{
	mWindow.create(sf::VideoMode(1920, 1080), "Hell on Treads v2.0.1");

	mMainMenu = std::make_unique<MainMenu>(mWindow);

	mPlayer.load();

	mEnemy.load();

	map.init();

	if (!map.parseMap())
		EXIT_FAILURE;
}

Core::~Core() = default;

void Core::run()
{
	while (mWindow.isOpen())
	{
		update(mDeltaTime);

		render(mWindow);

		startClock();
	}
}

void Core::update(float& deltaTime)
{
	processEvents();

	mPlayer.update(deltaTime);

	mPlayer.updatePositions(mWindow, deltaTime);

	mEnemy.update(deltaTime);

	mHUD.update(deltaTime);
}

void Core::processEvents()
{
	while (mWindow.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			mWindow.close();

		if (!mMainMenu->getIsClosed())
			mMainMenu->handleButtonEvents(e);
	}
}

void Core::startClock() { mDeltaTime = mDeltaTimeClock.restart().asSeconds(); }

void Core::render(sf::RenderTarget& target)
{
	mWindow.clear();

	if (!mMainMenu->getIsClosed())
		mMainMenu->render(target);

	if (mMainMenu->getIsClosed())
	{
		//map.drawMap(mWindow);

		mHUD.render(target);

		mPlayer.render(target);

		mEnemy.render(target);
	}

	mWindow.display();
}
