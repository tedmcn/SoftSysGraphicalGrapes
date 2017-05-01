#include <iostream>
#include "Cells.h"
#include "MazeBuilderEller.h"
using namespace std;

int main() {
	Cells c;
	MazeBuilderEller m;
	c = m.generateMaze();
	c.showMaze();
	return 0;
}
