#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>
#include <iostream>

class Maze
{
private:
	enum MazeCellType
	{
		WALL,
		VISITED,
		START,
		END,
		EMPTY,
		ON_PATH
	};
	std::vector < std::vector < MazeCellType >> MazeCells;
	void display(MazeCellType);
	int startRow;
	int startCol;
	MazeCellType read(char);
	bool solve(int, int);
public:
	Maze();
	void displayMaze();
	void solveMaze();
	void readFile(std::string filename);
};


#endif;