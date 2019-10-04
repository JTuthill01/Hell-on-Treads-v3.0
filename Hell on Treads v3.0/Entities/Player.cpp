#include "pch.hpp"
#include "Player.hpp"

extern int gVariables::gHp = 10;
extern int gVariables::gHpMax = 10;
extern int gVariables::gProjectiles = 20;
extern int gVariables::gProjectilesMax = 20;

std::vector<sf::Texture> Player::playerProjectile;

Player::Player() : mDistance(0.F), mSpeed(0.F), mTime(0.F), mStart(0.F), mEnd(0.F)
{
	mTurretSprite.setPosition(sf::Vector2f((mPlayerSprite.getPosition().x) + (mPlayerSprite.getLocalBounds().width / 2), (mPlayerSprite.getPosition().y) + (mPlayerSprite.getLocalBounds().height - 50.F)));

	setAnimations(mTreadsSprite, mTreadsTexture);

	setExplosionAnimations(mExplosionSprite, mExplosionTexture);
	
	mShootTimer.restart(sf::seconds(0.2F));
}

Player::~Player() = default;

void Player::load()
{
	if (!mPlayerTexture.loadFromFile("Resources/Sprites/Player/Hull.png"))
		std::cerr << "";

	if (!mTurretTexture.loadFromFile("Resources/Sprites/Player/Gun_1.png"))
		std::cerr << "";

	if (!mTreadsTexture.loadFromFile("Resources/Sprites/Player/test1.png"))
		std::cerr << "";

	if (!mGunTexture.loadFromFile("Resources/Sprites/Player/Gun_1_A.png"))
		std::cerr << "";

	if (!mExplosionTexture.loadFromFile("Resources/Sprites/Effects/4.png"))
		std::cerr << "";

	mPlayerSprite.setTexture(mPlayerTexture);

	mPlayerSprite.setPosition(sf::Vector2f(800.F, 700.F));

	mPlayerSprite.setOrigin(mPlayerSprite.getLocalBounds().width / 2, mPlayerSprite.getLocalBounds().height / 2 + 50);

	mTurretSprite.setTexture(mTurretTexture);

	mTurretSprite.setOrigin(mTurretSprite.getLocalBounds().width / 2, mTurretSprite.getLocalBounds().height / 2);

	mGunSprite.setTexture(mGunTexture);

	mGunSprite.setOrigin(mTurretSprite.getLocalBounds().width / 2 - 18, mTurretSprite.getLocalBounds().height / 2 + 98);

	mProjectile.setOrigin(mTurretSprite.getLocalBounds().width / 2 + 25, mTurretSprite.getLocalBounds().height / 2 + 190);

	mTreadsSprite.setTexture(mTreadsTexture);

	mTreadsSprite.setOrigin(mPlayerSprite.getLocalBounds().width / 2, mPlayerSprite.getLocalBounds().height / 2 + 50);

	mExplosionSprite.setTexture(mExplosionTexture);

	mExplosionSprite.setOrigin(mTurretSprite.getLocalBounds().width + 190, mTurretSprite.getLocalBounds().height + 310);
}

void Player::takeDamage(int damage)
{
	damage -= gVariables::gHp;

	if (gVariables::gHp <= 0)
		gVariables::gHp = 0;
}

void Player::updatePositions(sf::RenderWindow& window, float& deltaTime)
{
	moveTurretSprite(window, deltaTime);

	shootDirection(window, deltaTime);
}

sf::Vector2f Player::getPlayerPosition()
{
	playerPosition = mPlayerSprite.getPosition();

	return playerPosition;
}

void Player::setPositions(float & deltaTime)
{
	mTurretSprite.setPosition(mPlayerSprite.getPosition().x, mPlayerSprite.getPosition().y);

	mGunSprite.setPosition(mPlayerSprite.getPosition().x, mPlayerSprite.getPosition().y);

	mTreadsSprite.setPosition(sf::Vector2f((mPlayerSprite.getPosition().x - 70 + mPlayerSprite.getLocalBounds().width / 2.F) - 60.F, mPlayerSprite.getPosition().y + 
		(mPlayerSprite.getLocalBounds().height / 4.5F) - 70));

	mProjectile.getProjectile().setPosition(playerCenter);

	mExplosionSprite.setPosition(mTurretSprite.getPosition().x, mTurretSprite.getPosition().y);
}

void Player::moveTurretSprite(sf::RenderWindow& window, float & deltaTime)
{
	sf::Vector2f position = mTurretSprite.getPosition();
	sf::Vector2i cursorPosition = sf::Mouse::getPosition(window);

	float dX = cursorPosition.x - position.x;
	float dY = cursorPosition.y - position.y;

	float rotation = (atan2(dY, dX) * 180) / thor::Pi;

	mTurretSprite.setRotation(rotation + 90.F);

	mGunSprite.setRotation(rotation + 90.F);

	mProjectile.setRotation(rotation + 90.F);

	mExplosionSprite.setRotation(rotation + 90.F);
}

void Player::input(float & deltaTime)
{
	float temp = mPlayerSprite.getPosition().x + mPlayerSprite.getPosition().y;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		startClock();

		mPlayerSprite.move(-rotate.x, -rotate.y);

		move(0.F, -0.1F, deltaTime);

		mStart = temp - (mPlayerSprite.getPosition().x + mPlayerSprite.getPosition().y);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		startClock();

		mPlayerSprite.move(rotate.x, rotate.y);

		move(0.F, 0.1F, deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		mPlayerSprite.rotate(-0.1F);

		mTreadsSprite.rotate(-0.1F);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		mPlayerSprite.rotate(0.1F);

		mTreadsSprite.rotate(0.1F);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mShootTimer.isExpired())
	{
		move(1.F, 1.F, deltaTime);

		mMuzzleTimer.restart(sf::seconds(1.6F));

		mProjectile.currentVelocity = aimDirectionNormalized * mProjectile.maxSpeed;

		mProjectiles.push_back(Projectiles(mProjectile));

		mShootTimer.restart(sf::seconds(0.6F));

		pIsMuzzleOn = true;
	}

	for (size_t i = 0; i < mProjectiles.size(); i++)
		mProjectiles[i].getProjectile().move(mProjectiles[i].currentVelocity);

	if(mMuzzleTimer.isExpired())
		pIsMuzzleOn = false;
}

void Player::shootDirection(sf::RenderWindow& window, float& deltaTime)
{
	playerCenter = sf::Vector2f(mGunSprite.getPosition().x, mGunSprite.getPosition().y);

	mousePositionWindow = sf::Vector2f(sf::Mouse::getPosition(window));

	aimDirection = mousePositionWindow - playerCenter;

	aimDirectionNormalized = aimDirection / sqrt(pow(aimDirection.x, 2) + pow(aimDirection.y, 2));
}

void Player::startClock() { mTime = mTimeClock.restart().asSeconds(); }

sf::Vector2f Player::direction()
{
	rotate = thor::rotatedVector(sf::Vector2f(0, 0.5F), mPlayerSprite.getRotation());

	return rotate;
}

float Player::getSpeed()
{
	mDistance = mStart - mEnd;

	mSpeed = mDistance / mTime;

	return mSpeed;
}

void Player::update(float & deltaTime)
{
	getPlayerPosition();

	direction();

	setPositions(deltaTime);

	input(deltaTime);

	updateAnimations(deltaTime);

	updateExplosionAnimations(deltaTime);

	getSpeed();
}

void Player::render(sf::RenderTarget & target)
{
	target.draw(mTreadsSprite);

	target.draw(mPlayerSprite);

	target.draw(mTurretSprite);

	target.draw(mGunSprite);

	if(pIsMuzzleOn)
		target.draw(mExplosionSprite);

	for (size_t i = 0; i < mProjectiles.size(); i++)
		mProjectiles[i].render(target);
}
