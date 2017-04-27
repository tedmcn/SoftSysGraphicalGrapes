
#ifndef CELLS_H_
#define CELLS_H_

#include "Constants.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Cells {
public:
	Cells();
	virtual ~Cells();
	int getValueOfCell(int row, int cell);
	void setTopWall(int row, int cell, bool on);
	void setBottomWall(int row, int cell, bool on);
	void setLeftWall(int row, int cell, bool on);
	void setRightWall(int row, int cell, bool on);
	void printCells();
	void showMaze();
private:
	static const int width = 11;
	static const int height = 10;
	int cells[height][width];
};

#endif 
