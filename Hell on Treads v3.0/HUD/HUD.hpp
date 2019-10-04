#pragma once
#include "GlobalVariables.h"

class HUD
{
public:
	HUD();
	~HUD();

	void render(sf::RenderTarget& target);
	void update(float& deltaTime);

private:
	void load();
	void setRank();

	sf::Texture mHUDTexture;
	sf::Sprite mHUDSprite;

	sf::Texture mRankTexture;
	sf::Sprite mRankSprite;

	sf::Font mFont;
	sf::Text mRankText;
	sf::Text mScoreText;
	sf::Text mHpText;
	sf::Text mAmmoText;

	int mRank;

	bool mIsLoaded;
};