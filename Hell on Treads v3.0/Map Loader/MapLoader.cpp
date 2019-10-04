#include "pch.hpp"
#include "MapLoader.hpp"

MapLoader::MapLoader() = default;

MapLoader::~MapLoader() = default;

void MapLoader::init(const fs::path& basePath)
{
	mBasePath = basePath;
}

void MapLoader::renderMap(tson::Layer& layer, sf::RenderWindow& window)
{
	tson::Tileset* tileset = m_map.getTileset("NewTest");

	for (auto& layer : m_map.getLayers())
	{
		switch (layer.getType())
		{
		case tson::Layer::Type::TileLayer:

			drawTileLayer(layer, tileset, window);

			break;

		case tson::Layer::Type::ObjectGroup:
			//TODO: Implement
			break;

		case tson::Layer::Type::ImageLayer:
			//TODO: Implement
			break;

		case tson::Layer::Type::Group:
			//TODO: Implement
			break;

		default:
			break;
		}
	}
}

void MapLoader::drawMap(sf::RenderWindow& window)
{
	for (auto& layer : m_map.getLayers())
	{
		renderMap(layer, window);
	}
}

void MapLoader::drawTileLayer(tson::Layer& layer, tson::Tileset* tileset, sf::RenderWindow& window)
{
	int firstId = tileset->getFirstgid(); //First tile id of the tileset
	int columns = tileset->getColumns(); //For the demo map it is 8.
	int rows = tileset->getTileCount() / columns;
	int lastId = (tileset->getFirstgid() + tileset->getTileCount()) - 1;

	//pos = position in tile units
	for (auto& [pos, tile] : layer.getTileData()) //Loops through absolutely all existing tiles
	{
		fs::path imagePath;
		std::string pathStr;

		//With this, I know that it's related to the tileset above (though I only have one tileset)
		if (tile->getId() >= firstId && tile->getId() <= lastId)
		{
			//Get position in pixel units
			tson::Vector2f position = { (float)std::get<0>(pos) * m_map.getTileSize().x, (float)std::get<1>(pos) * m_map.getTileSize().y };

			int baseTilePosition = (tile->getId() - firstId);

			int tileModX = (baseTilePosition % columns);
			int currentRow = (baseTilePosition / columns);
			int offsetX = (tileModX != 0) ? ((tileModX)* m_map.getTileSize().x) : (0 * m_map.getTileSize().x);
			int offsetY = (currentRow < rows - 1) ? (currentRow * m_map.getTileSize().y) : ((rows - 1) * m_map.getTileSize().y);

			//Set sprite data to draw the tile
			mSprite.setTextureRect({ offsetX, offsetY, m_map.getTileSize().x, m_map.getTileSize().y });
			mSprite.setPosition({ position.x, position.y });
			window.draw(mSprite);
		}
	}
}

bool MapLoader::parseMap(const std::string& filename)
{
	tson::Tileson t;
	m_map = t.parse(fs::path(mBasePath / filename));

	fs::path demoTilesetPath = mBasePath / m_map.getTileset("NewTest")->getImage();

	if (m_map.getStatus() == tson::Map::ParseStatus::OK)
	{
		if (fs::exists(demoTilesetPath))
		{
			mTexture.loadFromFile(demoTilesetPath.u8string());
			mSprite.setTexture(mTexture);

			return true;
		}
		else
			std::cout << "Invalid Demo Tileset Path: " << demoTilesetPath.u8string() << std::endl;
	}
	else
		std::cout << "Parse error: " << m_map.getStatusMessage() << std::endl;

	return false;
}
