#include "pch.hpp"
#include "Animations.hpp"

Animations::Animations() : pAnimationComponent(nullptr), pMovementComponent(nullptr)
{
}

Animations::~Animations()
{
	delete pAnimationComponent;

	delete pMovementComponent;
}

void Animations::move(const float direction_x, const float direction_y, float& deltaTime)
{
	if (pMovementComponent)
		pMovementComponent->move(direction_x, direction_y, deltaTime);
}

void Animations::createMovementComponent(sf::Sprite& sprite, const float max_velocity, const float acceleration, const float deceleration)
{
	pMovementComponent = new MovementComponent(sprite, max_velocity, acceleration, deceleration);
}

void Animations::createAnimationComponent(sf::Sprite& sprite, sf::Texture texture_sheet)
{
	pAnimationComponent = new AnimationComponent(sprite, texture_sheet);
}
