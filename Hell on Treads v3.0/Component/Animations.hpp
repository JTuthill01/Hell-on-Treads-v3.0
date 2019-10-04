#pragma once
#include "AnimationComponent.h"
#include "MovementComponent.h"

class Animations
{
public:
	Animations();
	~Animations();

protected:

	virtual void move(const float direction_x, const float direction_y, float& deltaTime);
	virtual void createMovementComponent(sf::Sprite& sprite, const float max_velocity, const float acceleration, const float deceleration);
	virtual void createAnimationComponent(sf::Sprite& sprite, sf::Texture texture_sheet);

	AnimationComponent* pAnimationComponent;
	MovementComponent* pMovementComponent;
};