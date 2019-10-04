#include "Entities.hpp"

class Player : public Entities
{
public:
	Player();
	virtual ~Player();

	// Inherited via Entities
	virtual void update(float& deltaTime) override;
	virtual void render(sf::RenderTarget& target) override;
	virtual void load() override;

	void takeDamage(int damage);
	void updatePositions(sf::RenderWindow& window, float& deltaTime);
	
	static std::vector<sf::Texture> playerProjectile;

	inline sf::Sprite getPlayerSprite() { return mPlayerSprite; }
	inline sf::Vector2f getPlayerPosition();
	sf::Vector2f playerPosition;

private:
	void setPositions(float& deltaTime);
	void moveTurretSprite(sf::RenderWindow& window, float& deltaTime);
	void input(float& deltaTime);
	void shootDirection(sf::RenderWindow& window, float& deltaTime);
	void startClock();
	
	thor::Timer mShootTimer;
	thor::Timer mMuzzleTimer;

	sf::Sprite mExplosionSprite;
	sf::Sprite mPlayerSprite;
	sf::Sprite mTurretSprite;
	sf::Sprite mTreadsSprite;
	sf::Sprite mGunSprite;

	sf::Texture mExplosionTexture;
	sf::Texture mGunTexture;
	sf::Texture mPlayerTexture;
	sf::Texture mTurretTexture;
	sf::Texture mTreadsTexture;

	sf::View v;
	sf::Vector2f direction();
	sf::Vector2f rotate;
	sf::Vector2f playerCenter;
	sf::Vector2f mousePositionWindow;
	sf::Vector2f aimDirection;
	sf::Vector2f aimDirectionNormalized;

	Projectiles mProjectile;
	std::vector<Projectiles> mProjectiles;

	float getSpeed();
	float mSpeed;
	float mDistance;
	float mTime;
	float mStart;
	float mEnd;

	sf::Clock mTimeClock;
};