#ifndef NON_TILED_GRID_MANAGER
#define NON_TILED_GRID_MANAGER


class NonTiledGridManager {
private:
	sf::Vector2i tileCounts;
	sf::Vector2f origin;
	float tileSize;

public:
	NonTiledGridManager();
	~NonTiledGridManager();
	void initialize();
	void clean();



	void drawNonTiledGrid();

};



#endif
