#include "MapRenderer.h"
#include <math.h>

void MapRenderer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Draw shit yo.
	target.draw(*this->sprite, states);
}

MapRenderer::MapRenderer()
{
	this->sprite = new sf::Sprite();
	this->texture = new sf::Texture();

	std::string filePath = "../slimeTrail.png";
	std::string fileName = "slime";

	if (!texture->loadFromFile(filePath.c_str()))
		std::cout << "ERROR: " << fileName.c_str() << " failed to load!";
	else
		this->sprite->setTexture(*texture);

	this->sprite->setPosition(100, 100);
	this->sprite->setScale(2.0f, 2.0f);
}

MapRenderer::~MapRenderer()
{
	delete this->sprite;
	delete this->texture;
}

sf::Vector2f MapRenderer::toIsometric(sf::Vector2f vector)
{
	return sf::Vector2f {
		vector.x - vector.y,
		(vector.x + vector.y) * 0.5f
	};
}

sf::Vector2f MapRenderer::normalize(sf::Vector2f vector)
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

void MapRenderer::drawLine(sf::Vector2f origin)
{
	sf::RectangleShape line(sf::Vector2f(
		10.0f,	// Height
		0.5f	// Width
	));
	line.setPosition(Locator::getRenderWindow()->mapPixelToCoords(sf::Vector2i(origin)));

	Locator::getRenderWindow()->draw(line);
}

void MapRenderer::drawNonTiledGrid(sf::Vector2i tileCounts, float tileSize, sf::Vector2i origin)
{
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
		toIsometric(cartCorners[0]),	// North
		toIsometric(cartCorners[1]),	// East
		toIsometric(cartCorners[2]),	// South
		toIsometric(cartCorners[3])		// West
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
		vertices[addedSoFar++] = sf::Vertex(southEastLinesStart[i], sf::Color::Red);
		vertices[addedSoFar++] = sf::Vertex(southEastLinesFinish[i], sf::Color::Red);
	}
	// Add SouthWest to the VertexArray
	for (int i = 0; i < lineCount[DIRECTION::SOUTHWEST]; i++) {
		vertices[addedSoFar++] = sf::Vertex(southWestLinesStart[i], sf::Color::Blue);
		vertices[addedSoFar++] = sf::Vertex(southWestLinesFinish[i], sf::Color::Blue);
	}

	/// ---------------- DRAW VERTICES ----------------
	Locator::getRenderWindow()->draw(vertices, totalPointsCount, sf::Lines);


	delete southEastLinesStart;
	delete southEastLinesFinish;
	delete southWestLinesStart;
	delete southWestLinesFinish;
	delete vertices;
}

void MapRenderer::drawSquare(sf::Vector2i origin, float length)
{
	// Cartesian coordinates
	sf::Vector2f cartPoints[4] = {
		sf::Vector2f(origin.x, origin.y),
		sf::Vector2f(origin.x + length, origin.y),
		sf::Vector2f(origin.x + length, origin.y + length),
		sf::Vector2f(origin.x, origin.y + length)
	};
	// Same coordinates in Isometric
	sf::Vector2f isoPoints[4] = {
			toIsometric(cartPoints[0]),
			toIsometric(cartPoints[1]),
			toIsometric(cartPoints[2]),
			toIsometric(cartPoints[3])
	};

	// Move them into the first view properly
	for (int i = 0; i < 4; i++) {
		isoPoints[i].x += 50;
		isoPoints[i].y += 50;
	}

	// Construct indices-array based out of isometric points
	sf::Vertex indices[8] = {
		sf::Vertex(isoPoints[0], sf::Color::White, sf::Vector2f(0,0)),
		sf::Vertex(isoPoints[1], sf::Color::White, sf::Vector2f(0,0)),
		sf::Vertex(isoPoints[1], sf::Color::White, sf::Vector2f(0,0)),
		sf::Vertex(isoPoints[2], sf::Color::White, sf::Vector2f(0,0)),
		sf::Vertex(isoPoints[2], sf::Color::White, sf::Vector2f(0,0)),
		sf::Vertex(isoPoints[3], sf::Color::White, sf::Vector2f(0,0)),
		sf::Vertex(isoPoints[3], sf::Color::White, sf::Vector2f(0,0)),
		sf::Vertex(isoPoints[0], sf::Color::White, sf::Vector2f(0,0))
	};

	// Render the babies!
	Locator::getRenderWindow()->draw(indices, 8, sf::Lines);
}

void MapRenderer::initialize(sf::RenderWindow *renderWindow)
{
	this->view = new sf::View();

	view->reset(sf::FloatRect(
		0.0f,		// Origin-X
		0.0f,		// Origin-Y
		200.0f,		// Size-X
		200.0f		// Size-Y
	));
	view->setViewport(sf::FloatRect(
		0.0f,		// Origin-X
		0.0f,		// Origin-Y
		1.0f,		// Percentage-X
		1.0f		// Percentage-Y
	));
	renderWindow->setView(*view);
}

void MapRenderer::clean()
{
	delete this->view;
}

void MapRenderer::renderGrid() 
{
	sf::Vector2i origin{
	10,	// Number of x-tiles
	10	// Number of y-tiles
	};
	int length = 15;
	int size = 7;

	//	this->drawSquare(origin, length);
	sf::Vector2i counts{
		5,	// Number of x-tiles
		5	// Number of y-tiles
	};
	this->drawNonTiledGrid(counts, size, origin);

	//for (int x = 0; x < size; x++) {
	//	for (int y = 0; y < size; y++) {
	//		origin.x = 25 + x * length;
	//		origin.y = 25 + y * length;
	//		this->drawSquare(origin, length);
	//	}
	//}
}