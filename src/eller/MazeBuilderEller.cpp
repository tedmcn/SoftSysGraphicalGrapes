#include "MazeBuilderEller.h"

MazeBuilderEller::MazeBuilderEller() {}

MazeBuilderEller::~MazeBuilderEller() {}


Cells MazeBuilderEller::generateMaze() {
	srand(time(NULL));
	for (int x = 0; x < width; x++) sets[0][x] = x + 1;
	for (int y = 0; y < height; y++) {
		populateNext(y);
	}
	return cells;
}

/**
 * randomly join adjacent sets of a given row
 */
void MazeBuilderEller::joinSets(int row) {
	for (int cell = 0; cell < width - 1; cell++) {
		if (randomBool()) {
			breakWallHorizontal(row, cell);
		}
	}
}
/**
 * wrapper around `setWall` methods
 */
void MazeBuilderEller::breakWallHorizontal(int row, int cell) {
	cells.setRightWall(row, cell, false);
}
/**
 * populate the row after the one at index `row`
 */
void MazeBuilderEller::populateNext(int row) {
	if (row != height - 1) joinSets(row + 1);
	else joinLastRow();
}
/**
 * join all adjacent disjoint sets in the last row
 */
void MazeBuilderEller::joinLastRow() {
	int row = height - 1;
	for (int cell = 0; cell < width - 1; cell++) {
		if (sets[row][cell] != sets[row][cell + 1]) {
			cells.setRightWall(row, cell, false);
		}
	}
}

/**
 * helper methods
 */
bool MazeBuilderEller::randomBool() {
	return rand() % 2 == 1;
}

/**
 * debugger methods
 */
void MazeBuilderEller::printSets() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (x < width - 1) cout << sets[y][x] << " ";
			else cout << sets[y][x] << endl;
		}
	}
}
