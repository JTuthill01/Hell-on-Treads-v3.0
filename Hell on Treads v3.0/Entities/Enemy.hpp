#pragma once
#include "Entities.hpp"
#include "Player.hpp"

class Enemy : public Entities
{
public:
	Enemy();
	virtual ~Enemy();

	// Inherited via Entities
	virtual void load() override;
	virtual void update(float& deltaTime) override;
	virtual void render(sf::RenderTarget& target) override;

	inline int getEnemyHp() { return mHp; }

private:
	void setPositions(float& deltaTime);
	void moveTurretSprite(float& deltaTime);
	void shootDirection(float& deltaTime);

	int mHp;

	sf::Sprite mEnemyHullSprite;
	sf::Sprite mEnemyTurretSprite;
	sf::Sprite mEnemyTreadsSprite;
	sf::Sprite mEnemyGunSprite;

	sf::Texture mEnemyHullTexture;
	sf::Texture mEnemyTurretTexture;
	sf::Texture mEnemyTreadsTexture;
	sf::Texture mEnemyGunTexture;

	Player mPlayer;
};

