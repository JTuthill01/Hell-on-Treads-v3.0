#include "pch.hpp"
#include "HUD.hpp"

extern int gVariables::gScore = 0;
extern int gVariables::gProjectiles;
extern int gVariables::gProjectilesMax;
extern int gVariables::gHp;
extern int gVariables::gHpMax;

HUD::HUD() : mIsLoaded(true)
{
	mRank = gVariables::gScore;

	load();
}

HUD::~HUD() = default;

void HUD::render(sf::RenderTarget& target)
{
	target.draw(mHpText);

	target.draw(mAmmoText);

	target.draw(mScoreText);

	target.draw(mRankText);

	target.draw(mRankSprite);

	target.draw(mHUDSprite);
}

void HUD::update(float& deltaTime)
{
	setRank();

	mScoreText.setString(std::to_string(gVariables::gScore));

	std::stringstream remainingAmmo;

	remainingAmmo << gVariables::gProjectiles << "/" << gVariables::gProjectilesMax;

	mAmmoText.setString(remainingAmmo.str());

	std::stringstream remainingHp;

	remainingHp << gVariables::gHp << "/" << gVariables::gHpMax;

	mHpText.setString(remainingHp.str());
}

void HUD::load()
{
	if (!mHUDTexture.loadFromFile("Resources/Sprites/HUD/HUD.png"))
		 EXIT_FAILURE;

	if (!mFont.loadFromFile("Resources/Fonts/Anton-Regular.ttf"))
		EXIT_FAILURE;

	if (!mRankTexture.loadFromFile("Resources/Sprites/Rank/E2.png"))
		EXIT_FAILURE;

	mHUDSprite.setTexture(mHUDTexture);
	mHUDSprite.setPosition(100.F, -100.F);

	mRankSprite.setTexture(mRankTexture);
	mRankSprite.setPosition(0.F, -60.F);
	mRankSprite.setScale(0.8F, 0.8F);

	mRankText.setFont(mFont);
	mRankText.setCharacterSize(40U);
	mRankText.setFillColor(sf::Color::White);
	mRankText.setString("Rank");
	mRankText.setPosition(sf::Vector2f(0.F, 0.F));

	mScoreText.setFont(mFont);
	mScoreText.setCharacterSize(50U);
	mScoreText.setFillColor(sf::Color::White);
	mScoreText.setPosition(1860, 0.F);

	mAmmoText.setFont(mFont);
	mAmmoText.setCharacterSize(50U);
	mAmmoText.setFillColor(sf::Color::White);
	mAmmoText.setPosition(sf::Vector2f(60.F, 950.F));

	mHpText.setFont(mFont);
	mHpText.setCharacterSize(50U);
	mHpText.setFillColor(sf::Color::White);
	mHpText.setPosition(sf::Vector2f(1600.F, 950.F));
}

void HUD::setRank()
{
	if (mRank == 20)
	{
		if (mIsLoaded)
		{
			if (!mRankTexture.loadFromFile("Resources/Sprites/Rank/E3.png"))
			{
				EXIT_FAILURE;

				mIsLoaded = false;
			}
		}
	}
}
