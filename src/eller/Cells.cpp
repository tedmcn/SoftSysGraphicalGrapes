#include "Cells.h"

Cells::Cells() {
	for (int row = 0; row < height; row++) {
		for (int cell = 0; cell < width; cell++) {
			cells[row][cell] = WALL_ALL;
		}
	}
}

Cells::~Cells() {}

int Cells::getValueOfCell(int row, int cell) {
	return cells[row][cell];
}

// also takes care of its neighbors wall
void Cells::setTopWall(int row, int cell, bool on) {
	if (row == 0) return;
	if (on) {
		cells[row][cell] |= WALL_TOP;
		cells[row - 1][cell] |= WALL_BOTTOM;
	} else {
		cells[row][cell] &= ~WALL_TOP;
		cells[row - 1][cell] &= ~WALL_BOTTOM;
	}
};

void Cells::setBottomWall(int row, int cell, bool on) {
	if (row == height - 1) return;
	if (on) {
		cells[row][cell] |= WALL_BOTTOM;
		cells[row + 1][cell] |= WALL_TOP;
	} else {
		cells[row][cell] &= ~WALL_BOTTOM;
		cells[row + 1][cell] &= ~WALL_TOP;
	}
};

void Cells::setLeftWall(int row, int cell, bool on) {
	if (cell == 0) return;
	if (on) {
		cells[row][cell] |= WALL_LEFT;
		cells[row][cell - 1] |= WALL_RIGHT;
	} else {
		cells[row][cell] &= ~WALL_LEFT;
		cells[row][cell - 1] &= ~WALL_RIGHT;
	}
};

void Cells::setRightWall(int row, int cell, bool on) {
	if (cell == width - 1) return;
	if (on) {
		cells[row][cell] |= WALL_RIGHT;
		cells[row][cell + 1] |= WALL_LEFT;
	} else {
		cells[row][cell] &= ~WALL_RIGHT;
		cells[row][cell + 1] &= ~WALL_LEFT;
	}
};

void Cells::printCells() {
	for (int row = 0; row < height; row++) {
		for (int cell = 0; cell < width; cell++) {
			if (cell < width - 1) cout << cells[row][cell] << " ";
			else cout << cells[row][cell] << endl;
		}
	}
}

void Cells::showMaze() {
	string o = "var width = " + to_string(width) + ";\n";
	o += "var height = " + to_string(height) + ";\n";
	o += "var cells = ";
	o += "[\n";
	for (int row = 0; row < height; row++) {
		o += "\t[";
		for (int cell = 0; cell < width; cell++) {
			if (cell < width - 1) o += to_string(cells[row][cell]) + ",";
			else o += to_string(cells[row][cell]);
		}
		if (row < height - 1) o += "],\n";
		else o += "]\n";
	}
	o += "];\n";
	ofstream file;
	file.open("OUT.txt");
	file << o;
	file.close();
}
