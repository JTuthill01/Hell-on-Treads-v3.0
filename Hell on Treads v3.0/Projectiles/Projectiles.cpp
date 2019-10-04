#include "pch.hpp"
#include "Projectiles.hpp"

Projectiles::Projectiles() : maxSpeed(1.F)
{
	if (!mTexture.loadFromFile("Resources/Sprites/Player/Shell.png"))
		std::cerr << "";

	mProjectileSprite.setTexture(mTexture);
}

Projectiles::Projectiles(sf::Texture* texture) : mProjectileTexture(texture), maxSpeed(5.F)
{
	mProjectileSprite.setTexture(*mProjectileTexture);
}

Projectiles::Projectiles(sf::Texture * texture, sf::Vector2f position, sf::Vector2f scale) : mExplosionTexture(nullptr), mProjectileTexture(nullptr)
{
	mExplosionTexture = texture;

	mExplosionPosition = position;

	mExplosionScale = scale;

	mExplosionSprite.setTexture(*mExplosionTexture);
	mExplosionSprite.setPosition(mExplosionPosition);
	mExplosionSprite.setScale(mExplosionScale);
}

Projectiles::Projectiles(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f direction) : mProjectileTexture(nullptr), mExplosionTexture(nullptr)
{
	mProjectileTexture = texture;

	mPosition = position;

	mScale = scale;

	mDirection = direction;

	mProjectileSprite.setTexture(*mProjectileTexture);
	mProjectileSprite.setScale(mScale);
	mProjectileSprite.setPosition(mPosition);
}

Projectiles::~Projectiles() = default;

void Projectiles::render(sf::RenderTarget & target)
{
	target.draw(mProjectileSprite);

	target.draw(mExplosionSprite);
}

void Projectiles::update(float & deltaTime)
{
	mProjectileSprite.move(mDirection);
}

