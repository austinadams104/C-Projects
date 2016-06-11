#include "Maze.h"


int main()
{
	Maze m;
	std::string filename;
	
	m.readFile(filename);
	m.displayMaze();
	m.solveMaze();
	std::cout << std::endl;
	m.displayMaze();
	

	char dummy;
	std::cin >> dummy;
}