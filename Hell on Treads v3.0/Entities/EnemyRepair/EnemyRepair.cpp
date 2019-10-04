#include "pch.hpp"
#include "EnemyRepair.hpp"

EnemyRepair::EnemyRepair() : mIsDestoryed(false), mIsHit(false), mIsRepairNeeded(false), mAmbulanceHp(10), mIsAlive(true), mBuildingHp(15)
{
	load();

	setAnimations();
}

EnemyRepair::~EnemyRepair() = default;

void EnemyRepair::renderAmbulance(sf::RenderTarget & target) 
{ 
	if(mIsRepairNeeded)
		target.draw(mAmbulanceSprite); 
}

void EnemyRepair::renderBuilding(sf::RenderTarget& target) { target.draw(mBuildingSprite); }

void EnemyRepair::buildingTakeDamage(int damage)
{
	damage -= mBuildingHp;

	if (mBuildingHp <= 0)
	{
		mBuildingHp = 0;

		mIsDestoryed = true;
	}

	if (mIsHit)
	{
		mBuildingSprite.setTexture(mBuildingHitTexture);

		mBuildingHitTimer.restart(sf::seconds(0.2F));
	}

	if (mBuildingHitTimer.isExpired())
	{
		mIsHit = false;

		mBuildingSprite.setTexture(mBuildingTexture);
	}
}

void EnemyRepair::ambulanceTakeDamage(int damage)
{
	damage -= mAmbulanceHp;

	if (mAmbulanceHp <= 0)
	{
		mAmbulanceHp = 0;

		mIsAlive = false;
	}
}

void EnemyRepair::update(float & deltaTime)
{
	if (mIsRepairNeeded)
		pAnimationComponent->play("MOVE", deltaTime);
}

void EnemyRepair::setAnimations()
{
	createMovementComponent(mAmbulanceSprite, 350.F, 16.F, 6.F);

	createAnimationComponent(mAmbulanceSprite, mAmbulanceTexture);

	pAnimationComponent->addAnimation("IDLE", 50.F, 0, 0, 2, 0, 256, 256);
	pAnimationComponent->addAnimation("MOVE", 50.F, 0, 0, 2, 0, 256, 256);
}

void EnemyRepair::load()
{
	if (!mBuildingTexture.loadFromFile("Resources/Sprites/Enemy/Repair/Building/bunker.png"))
		EXIT_FAILURE;

	if (!mBuildingHitTexture.loadFromFile("Resources/Sprites/Enemy/Repair/Building/bunker_hit.png"))
		EXIT_FAILURE;

	if (!mBuildingDestroytedTexture.loadFromFile("Resources/Sprites/Enemy/Repair/Building/bunker_destroyed.png"))
		EXIT_FAILURE;

	if (!mRubbleTexture.loadFromFile("Resources/Sprites/Enemy/Repair/Building/ruin.png"))
		EXIT_FAILURE;

	if (!mAmbulanceTexture.loadFromFile("Resources/Sprites/Enemy/Repair/Ambulance/Ambulance.png"))
		EXIT_FAILURE;

	mBuildingSprite.setTexture(mBuildingTexture);

	mAmbulanceSprite.setTexture(mAmbulanceTexture);
}

void EnemyRepair::spawnAmbulance()
{
	if (mEnemy.getEnemyHp() <= 5 && mIsDestoryed != true)
		mIsRepairNeeded = true;
}
