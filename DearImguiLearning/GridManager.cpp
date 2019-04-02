#include "GridManager.h"
#include "Locator.hpp"

void GridManager::generateGrid()
{
	sf::Vector2f origin = this->origin;
	sf::Vector2i tileCounts = this->tileCounts;
	float tileSize = this->tileSize;

	/// ---------------- CONVERTING FROM CARTESIAN INTO ISOMETRIC ----------------
	// Cartesian Corners
	sf::Vector2f cartCorners[4] = {
		sf::Vector2f(origin.x, origin.y),															// North
		sf::Vector2f(origin.x + (tileCounts.x * tileSize), origin.y),								// East
		sf::Vector2f(origin.x + (tileCounts.x * tileSize), origin.y + (tileCounts.y * tileSize)),	// South
		sf::Vector2f(origin.x, origin.y + (tileCounts.y * tileSize)),								// West
	};
	// Isometric Corners
	sf::Vector2f isoCorners[4] = {
		this->toIsometric(cartCorners[0]),	// North
		this->toIsometric(cartCorners[1]),	// East
		this->toIsometric(cartCorners[2]),	// South
		this->toIsometric(cartCorners[3])	// West
	};

	/// ---------------- BUILDING VECTORS FOR OPTIMIZATION ----------------
	enum DIRECTION {
		SOUTHEAST,
		SOUTHWEST,
		COUNT
	};
	int lineCount[DIRECTION::COUNT];
	sf::Vector2f directionVectors[DIRECTION::COUNT];
	sf::Vector2f n_directionVectors[DIRECTION::COUNT];
	// LineCounts
	lineCount[DIRECTION::SOUTHEAST] = tileCounts.x + 1;		// There are always 1 more lines than there are tiles
	lineCount[DIRECTION::SOUTHWEST] = tileCounts.y + 1;		//
	// Generate DirectionVectors
	directionVectors[DIRECTION::SOUTHEAST] = (isoCorners[1] - isoCorners[0]);// *float((tileCounts.x - 1) / float(tileCounts.x));
	directionVectors[DIRECTION::SOUTHWEST] = sf::Vector2f(		// Optimized flip to southWest!
		directionVectors[DIRECTION::SOUTHEAST].x * (-1),		//
		directionVectors[DIRECTION::SOUTHEAST].y				//
	);															//
	// Normalize them!
	n_directionVectors[DIRECTION::SOUTHEAST] = normalize(directionVectors[DIRECTION::SOUTHEAST]);
	n_directionVectors[DIRECTION::SOUTHWEST] = sf::Vector2f(	// Optimized flip to southWest!
		n_directionVectors[DIRECTION::SOUTHEAST].x * (-1),		//
		n_directionVectors[DIRECTION::SOUTHEAST].y				//
	);															//
	// Fix old DirectionVectors!
	directionVectors[DIRECTION::SOUTHEAST] = n_directionVectors[DIRECTION::SOUTHEAST] * tileSize * float(lineCount[DIRECTION::SOUTHEAST] - 1);
	directionVectors[DIRECTION::SOUTHWEST] = n_directionVectors[DIRECTION::SOUTHWEST] * tileSize * float(lineCount[DIRECTION::SOUTHWEST] - 1);

	/// ---------------- GENERATE LINES ----------------
	/* OPTIMIZATION:
	- 4 points are currently being used twice
	- calculations can be done elsewhere once, saved, and re-used rather than repeated each frame
	*/
	// Generate lines!
	sf::Vector2f *southEastLinesStart = new sf::Vector2f[lineCount[DIRECTION::SOUTHEAST]];
	sf::Vector2f *southEastLinesFinish = new sf::Vector2f[lineCount[DIRECTION::SOUTHEAST]];
	sf::Vector2f *southWestLinesStart = new sf::Vector2f[lineCount[DIRECTION::SOUTHWEST]];
	sf::Vector2f *southWestLinesFinish = new sf::Vector2f[lineCount[DIRECTION::SOUTHWEST]];

	// Build SouthEastLinePoints!
	sf::Vector2f scaledDirection = n_directionVectors[DIRECTION::SOUTHEAST] * tileSize;
	for (int i = 0; i < lineCount[DIRECTION::SOUTHEAST]; i++) {
		southEastLinesStart[i] = sf::Vector2f(isoCorners[0] + scaledDirection * float(i));
		southEastLinesFinish[i] = southEastLinesStart[i] + directionVectors[DIRECTION::SOUTHWEST];
	}

	// Build SouthWestLinePoints!
	scaledDirection.x = scaledDirection.x * (-1);	// Optimized flip to a scaledDirection relative to SouthWest
	for (int i = 0; i < lineCount[DIRECTION::SOUTHWEST]; i++) {
		southWestLinesStart[i] = sf::Vector2f(isoCorners[0] + scaledDirection * float(i));
		southWestLinesFinish[i] = southWestLinesStart[i] + directionVectors[DIRECTION::SOUTHEAST];
	}

	/// ---------------- CONSTRUCTION OF VERTEXARRAY ----------------
	int totalPointsCount = 2 * (lineCount[DIRECTION::SOUTHEAST] + lineCount[DIRECTION::SOUTHWEST]);
	sf::Vertex *vertices = new sf::Vertex[totalPointsCount];
	int addedSoFar = 0;
	// Add SouthEast to the VertexArray
	for (int i = 0; i < lineCount[DIRECTION::SOUTHEAST]; i++) {
		vertices[addedSoFar++] = sf::Vertex(southEastLinesStart[i], sf::Color::White);
		vertices[addedSoFar++] = sf::Vertex(southEastLinesFinish[i], sf::Color::White);
	}
	// Add SouthWest to the VertexArray
	for (int i = 0; i < lineCount[DIRECTION::SOUTHWEST]; i++) {
		vertices[addedSoFar++] = sf::Vertex(southWestLinesStart[i], sf::Color::White);
		vertices[addedSoFar++] = sf::Vertex(southWestLinesFinish[i], sf::Color::White);
	}
	// Save the processed data!
	this->grid.vertices = vertices;
	this->grid.verticeCount = totalPointsCount;

	/// ---------------- CLEAN DYNAMICALLY ALLOCATED OBJECTS ----------------
	delete southEastLinesStart;
	delete southEastLinesFinish;
	delete southWestLinesStart;
	delete southWestLinesFinish;
}

sf::Vector2f GridManager::toIsometric(sf::Vector2f vector)
{
	return sf::Vector2f{
		vector.x - vector.y,
		(vector.x + vector.y) * 0.5f
	};
}

sf::Vector2f GridManager::normalize(sf::Vector2f vector)
{
	/* OPTIMIZATION:
	- Can be made faster by approximating 1/abs rather than calculating perfectly
	*/

	float length = (vector.x * vector.x) + (vector.y * vector.y);
	float abs = sqrt(length);
	float divider = 1 / abs;

	return sf::Vector2f{
		vector.x * divider,
		vector.y * divider
	};
}

GridManager::GridManager()
{
}

GridManager::~GridManager()
{
}

void GridManager::initialize(sf::Vector2i gridSize, sf::Vector2f origin, float tileSize)
{
	this->testTile.initialize(
		"../GameData/Assets/Textures/TileTextures/FirstTexture.png",
		sf::Vector2f(0.0f, 0.0f)
	);

	this->grid.tileCounts = gridSize;
	this->grid.origin = origin;
	this->grid.tileSize = tileSize;

	this->generateGrid();
}

void GridManager::clean()
{
	this->grid.clean();
}

void GridManager::test()
{
	(*Locator::getRenderWindow())->draw(this->testTile);
}

void GridManager::testRenderVoidTiles()
{
	(*Locator::getRenderWindow())->draw(this->grid.vertices, this->grid.verticeCount, sf::Lines);
}

void GridManager::renderCurrentGrid()
{
	// Draw the textured sprite-tile
	(*Locator::getRenderWindow())->draw(this->testTile);

	// Draw the manually created grid
	(*Locator::getRenderWindow())->draw(this->grid.vertices, this->grid.verticeCount, sf::Lines);
}
