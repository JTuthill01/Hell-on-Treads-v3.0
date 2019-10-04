#include "pch.hpp"
#include "Entities.hpp"

Entities::Entities() : mAnimationComponent(nullptr), mMovementComponent(nullptr), pDamage(1), pDamageMax(4), pIsAttacking(false), pIsMuzzleOn(false),
	mExplosionAnimationComponent(nullptr), mExplosionMovementComponent(nullptr)
{
}

Entities::~Entities()
{
	delete mAnimationComponent;

	delete mMovementComponent;

	delete mExplosionAnimationComponent;

	delete mExplosionMovementComponent;
}

const int Entities::dealDamage() const
{
	int damage = 0;

	damage = rand() % pDamage + pDamageMax;

	return damage;
}

void Entities::setAnimations(sf::Sprite & sprite, sf::Texture & texture)
{
	createMovementComponent(sprite, 350.F, 16.F, 6.F);

	createAnimationComponent(sprite, texture);
	createAnimationComponent(sprite, texture);

	mAnimationComponent->addAnimation("IDLE", 50.F, 0, 0, 0, 0, 256, 246);
	mAnimationComponent->addAnimation("MOVE", 16.F, 0, 0, 1, 0, 256, 246);
}

void Entities::setExplosionAnimations(sf::Sprite& sprite, sf::Texture& texture)
{
	createExplosionsMovementComponent(sprite, 350.F, 16.F, 6.F);

	createExplosionsAnimationComponent(sprite, texture);

	mExplosionAnimationComponent->addAnimation("BOOM", 30.F, 0, 0, 7, 0, 512, 512);
}

void Entities::updateAnimations(float& deltaTime)
{
	if (mMovementComponent->getState(IDLE))
		mAnimationComponent->play("IDLE", deltaTime);

	else if (mMovementComponent->getState(MOVING))
		mAnimationComponent->play("MOVE", deltaTime);

	mMovementComponent->update(deltaTime);
}

void Entities::updateExplosionAnimations(float & deltaTime)
{
	mExplosionAnimationComponent->play("BOOM", deltaTime);

	mExplosionMovementComponent->update(deltaTime);
}

void Entities::createMovementComponent(sf::Sprite & sprite, const float max_velocity, const float acceleration, const float deceleration)
{
	mMovementComponent = new MovementComponent(sprite, max_velocity, acceleration, deceleration);
}

void Entities::createAnimationComponent(sf::Sprite & sprite, sf::Texture texture_sheet)
{
	mAnimationComponent = new AnimationComponent(sprite, texture_sheet);
}

void Entities::move(const float direction_x, const float direction_y, float & deltaTime)
{
	if (mMovementComponent)
		mMovementComponent->move(direction_x, direction_y, deltaTime);
}

void Entities::createExplosionsMovementComponent(sf::Sprite& sprite, const float max_velocity, const float acceleration, const float deceleration)
{
	mExplosionMovementComponent = new MovementComponent(sprite, max_velocity, acceleration, deceleration);
}

void Entities::createExplosionsAnimationComponent(sf::Sprite& sprite, sf::Texture texture_sheet)
{
	mExplosionAnimationComponent = new AnimationComponent(sprite, texture_sheet);
}

void Entities::moveExplosions(const float direction_x, const float direction_y, float& deltaTime)
{
	if (mExplosionMovementComponent)
		mExplosionMovementComponent->move(direction_x, direction_y, deltaTime);
}
