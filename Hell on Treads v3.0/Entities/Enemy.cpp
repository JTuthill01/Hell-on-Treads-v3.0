#include "pch.hpp"
#include "Enemy.hpp"

Enemy::Enemy() : mHp(15)
{
	mEnemyHullSprite.setPosition(500.F, 500.F);

	setAnimations(mEnemyTreadsSprite, mEnemyTreadsTexture);
}

Enemy::~Enemy() = default;

void Enemy::load()
{
	if (!mEnemyHullTexture.loadFromFile("Resources/Sprites/Enemy/Hull.png"))
		std::cerr << "";

	if (!mEnemyTreadsTexture.loadFromFile("Resources/Sprites/Enemy/treads.png"))
		std::cerr << "";

	if (!mEnemyTurretTexture.loadFromFile("Resources/Sprites/Enemy/Gun.png"))
		std::cerr << "";

	if (!mEnemyGunTexture.loadFromFile("Resources/Sprites/Enemy/Gun_A.png"))
		std::cerr << "";

	mEnemyHullSprite.setTexture(mEnemyHullTexture);

	mEnemyHullSprite.setOrigin(mEnemyHullSprite.getLocalBounds().width / 2, mEnemyHullSprite.getLocalBounds().height / 2 + 50);

	mEnemyTreadsSprite.setTexture(mEnemyTreadsTexture);

	mEnemyTreadsSprite.setOrigin(mEnemyHullSprite.getLocalBounds().width / 2, mEnemyHullSprite.getLocalBounds().height / 2 + 50);

	mEnemyTurretSprite.setTexture(mEnemyTurretTexture);

	mEnemyTurretSprite.setOrigin(mEnemyTurretSprite.getLocalBounds().width / 2, mEnemyTurretSprite.getLocalBounds().height / 2);

	mEnemyGunSprite.setTexture(mEnemyGunTexture);

	mEnemyGunSprite.setOrigin(mEnemyTurretSprite.getLocalBounds().width / 2 - 18, mEnemyTurretSprite.getLocalBounds().height / 2 + 98);
}

void Enemy::update(float& deltaTime)
{
	setPositions(deltaTime);

	moveTurretSprite(deltaTime);

	updateAnimations(deltaTime);

	//mEnemyHullSprite.move(0.F, -0.1F);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(mEnemyTreadsSprite);

	target.draw(mEnemyHullSprite);

	target.draw(mEnemyTurretSprite);

	target.draw(mEnemyGunSprite);
}

void Enemy::setPositions(float& deltaTime)
{
	mEnemyTreadsSprite.setPosition(mEnemyHullSprite.getPosition().x, mEnemyHullSprite.getPosition().y);

	mEnemyTurretSprite.setPosition(mEnemyHullSprite.getPosition().x, mEnemyHullSprite.getPosition().y);

	mEnemyGunSprite.setPosition(mEnemyHullSprite.getPosition().x, mEnemyHullSprite.getPosition().y);
}

void Enemy::moveTurretSprite(float& deltaTime)
{
	sf::Vector2f position = mEnemyGunSprite.getPosition();
	sf::Vector2f aimDirection = mPlayer.getPlayerSprite().getPosition();

	float dX = aimDirection.x - position.x;
	float dY = aimDirection.y - position.y;

	float rotation = (atan2f(dY, dX)) * ((180 / thor::Pi) + 180);

	mEnemyTurretSprite.setRotation(rotation);

	mEnemyGunSprite.setRotation(rotation);
}

void Enemy::shootDirection(float& deltaTime)
{
}
