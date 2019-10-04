#pragma once
#include <Component/Animations.hpp>
#include "Entities/Enemy.hpp"

class EnemyRepair : public Animations
{
public:
	EnemyRepair();
	~EnemyRepair();

	void renderAmbulance(sf::RenderTarget& target);
	void renderBuilding(sf::RenderTarget& target);
	void buildingTakeDamage(int damage);
	void ambulanceTakeDamage(int damage);
	void update(float& deltaTime);

	inline void setIsHit(bool t_f) { mIsHit = t_f; }
	inline bool getIsHit() { return mIsHit; }
	inline bool getIsAmbulanceAlive() { return mIsAlive; }

private:
	void setAnimations();
	void load();
	void spawnAmbulance();

	bool mIsRepairNeeded;
	bool mIsDestoryed;
	bool mIsHit;
	bool mIsAlive;

	int mAmbulanceHp;
	int mBuildingHp;

	sf::Texture mAmbulanceTexture;
	sf::Sprite mAmbulanceSprite;

	sf::Texture mBuildingTexture;
	sf::Texture mBuildingHitTexture;
	sf::Texture mBuildingDestroytedTexture;
	sf::Texture mRubbleTexture;
	sf::Sprite mBuildingSprite;

	thor::Timer mBuildingHitTimer;

	Enemy* mEnemy;
};