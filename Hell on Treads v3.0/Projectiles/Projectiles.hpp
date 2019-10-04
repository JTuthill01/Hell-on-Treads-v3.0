#pragma once

enum projectileType { TORPEDO = 0, SAM};

enum explosionType { EXPLOSION = 0, TARGET_DESTROYED };

class Projectiles
{
public:
	Projectiles();
	Projectiles(sf::Texture* texture);
	Projectiles(sf::Texture * texture, sf::Vector2f position, sf::Vector2f scale);
	Projectiles(sf::Texture* texture, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f direction);
	~Projectiles();

	void render(sf::RenderTarget& target);
	void update(float& deltaTime);

	inline void setRotation(float radian) { mProjectileSprite.setRotation(radian); }
	inline void setOrigin(float x, float y) { mProjectileSprite.setOrigin(x, y); }
	inline sf::FloatRect getLocalBounds() { return mProjectileSprite.getLocalBounds(); }
	inline sf::Vector2f getProjectilePosition() { return mProjectileSprite.getPosition(); }
	inline sf::Sprite& getProjectile() { return mProjectileSprite; }

	sf::Vector2f currentVelocity;

	float maxSpeed;

private:
	sf::Texture mTexture;
	sf::Texture* mExplosionTexture;
	sf::Texture* mProjectileTexture;
	sf::Sprite mProjectileSprite;
	sf::Sprite mExplosionSprite;
	sf::Vector2f mPosition;
	sf::Vector2f mScale;
	sf::Vector2f mDirection;
	sf::Vector2f mExplosionPosition;
	sf::Vector2f mExplosionScale;
};

