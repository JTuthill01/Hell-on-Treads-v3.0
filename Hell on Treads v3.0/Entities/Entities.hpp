#pragma once
#include <Component/AnimationComponent.h>
#include <Component/MovementComponent.h>
#include <Projectiles/Projectiles.hpp>

#include "GlobalVariables.h"

class Entities
{
public:

	Entities();
	virtual ~Entities();

protected:

	virtual void load() = 0;
	virtual void update(float& deltaTime) = 0;
	virtual void render(sf::RenderTarget& target) = 0;

	virtual const int dealDamage() const;
	virtual void setAnimations(sf::Sprite& sprite, sf::Texture& texture);
	virtual void setExplosionAnimations(sf::Sprite& sprite, sf::Texture& texture);
	virtual void updateAnimations(float& deltaTime);
	virtual void updateExplosionAnimations(float& deltaTime);
	virtual void createMovementComponent(sf::Sprite& sprite, const float max_velocity, const float acceleration, const float deceleration);
	virtual void createAnimationComponent(sf::Sprite& sprite, sf::Texture texture_sheet);
	virtual void move(const float direction_x, const float direction_y, float& deltaTime);
	virtual void createExplosionsMovementComponent(sf::Sprite& sprite, const float max_velocity, const float acceleration, const float deceleration);
	virtual void createExplosionsAnimationComponent(sf::Sprite& sprite, sf::Texture texture_sheet);
	virtual void moveExplosions(const float direction_x, const float direction_y, float& deltaTime);

	int pDamage;
	int pDamageMax;

	bool pIsAttacking;
	bool pIsMuzzleOn;

private:
	AnimationComponent* mAnimationComponent;
	MovementComponent* mMovementComponent;

	AnimationComponent* mExplosionAnimationComponent;
	MovementComponent* mExplosionMovementComponent;

	sf::Vector2f mPosition;

	sf::Texture mExplosionTexture;
};

