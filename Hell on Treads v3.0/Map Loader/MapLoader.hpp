#pragma once
#include <tileson/src/Tileson.h>

class MapLoader
{
public:
	MapLoader();
	~MapLoader();

	void init(const fs::path& basePath = fs::path("Resources/Levels/"));
	void renderMap(tson::Layer& layer, sf::RenderWindow& window);
	void drawMap(sf::RenderWindow& window);
	bool parseMap(const std::string& filename = "Level1.json");

private:
	void drawTileLayer(tson::Layer& layer, tson::Tileset* tileset, sf::RenderWindow& window);
	
	tson::Map m_map;

	sf::Texture mTexture;
	sf::Sprite mSprite;

	fs::path mBasePath{};
};

