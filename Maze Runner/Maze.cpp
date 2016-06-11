#include "Maze.h"
#include <iostream>
#include <fstream>

Maze::Maze() : MazeCells(), startCol(), startRow()
{
}

void Maze::displayMaze()
{
	for (auto&& row : MazeCells)
	{
		for (auto&& cell : row)
		{
			display(cell);

		}
		std::cout << std::endl;
	}
}

void Maze::solveMaze()
{
	solve(startRow, startCol);
}

bool Maze::solve(int r, int c)
{
	if (MazeCells[r][c] == WALL)
		return false;
	if (MazeCells[r][c] == VISITED)
		return false;
	if (MazeCells[r][c] == END)
		return true;
	if (MazeCells[r][c] != START)
	{
	MazeCells[r][c] = VISITED;
	}

	if (solve(r - 1, c) || solve(r + 1, c) || solve(r, c - 1) || solve(r, c + 1))
	{
		if (MazeCells[r][c] != START)
		{
			MazeCells[r][c] = ON_PATH;
			return true;
		}
	}
	return false;
}

Maze::MazeCellType Maze::read(char c)
{
	switch (c)
	{
	case 'X':case'x': return WALL;
	case 'E':case'e': return END;
	case 'S':case's': return START;
	default: return EMPTY;
	}
	return EMPTY;
}

void Maze::display(Maze::MazeCellType c)
{
	switch (c)
	{
	case WALL:
		std::cout << "X";
		break;
	case EMPTY:
		std::cout << " ";
		break;
	case START:
		std::cout << "s";
		break;
	case END:
		std::cout << "e";
		break;
	case ON_PATH:
		std::cout << "*";
		break;
	case VISITED:
		std::cout << " ";
		break;
	default:
		std::cout << " ";
		break;

	}
}

void Maze::readFile(std::string filename)
{
	std::cout << "Welcome to the Magic Maze Solver!\n";
	std::cout << "Enter the maze file name to be solved: " << std::endl;
	std::getline(std::cin, filename);
	std::fstream fin(filename);
	while (!fin)
	{
		std::cout << "That was not a correct file name....\n";
		std::cout << "Write the file like this:  example.txt\n\n";
		std::cout << "Try again. Enter the file name:\n";
		std::getline(std::cin, filename);
		fin.open(filename);
	}
	auto r = 0;
	auto c = 0;
	fin >> r >> c;
	MazeCells.resize(r);
	for (auto && row: MazeCells)
	{
		row.resize(c);
	}
	for (auto curRow = 0; curRow < r; ++curRow)
	{
		for (auto curCol = 0; curCol < c; ++curCol)
		{
			char fromFile;
			fin >> fromFile;
			MazeCells[curRow][curCol] = read(fromFile);
			if (MazeCells[curRow][curCol] == START)
			{
				startRow = curRow;
				startCol = curCol;
			}
		}
	}
}


