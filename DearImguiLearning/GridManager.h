#ifndef GRIDMANAGER_H
#define GRIDMANAGER_H

#include "Tile.h"
/*
The GridManager class is responsible for dealing with every tile that exists!
It does so..
*/

class GridManager {
private:
	Tile** grid;
	Tile testTile;

public:
	GridManager();
	~GridManager();
	void initialize();
	void clean();

	void test();

};



#endif