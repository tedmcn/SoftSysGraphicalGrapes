#ifndef MAZEBUILDERELLER_H_
#define MAZEBUILDERELLER_H_

#include "Cells.h"
#include "Constants.h"
#include <stdlib.h>
#include <time.h>

class MazeBuilderEller {
public:
	MazeBuilderEller();
	virtual ~MazeBuilderEller();
	Cells generateMaze();
private:
	Cells cells;
	static const int width = 11;
	static const int height = 10;
	int sets[height][width];
	void joinSets(int row);
	void breakWallHorizontal(int row, int cell);
	void populateNext(int row);
	void joinLastRow();
	void printSets();
	bool randomBool();
};

#endif 
