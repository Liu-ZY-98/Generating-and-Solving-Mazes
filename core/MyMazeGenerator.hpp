#ifndef MYMAZEGENERATOR_HPP
#define MYMAZEGENERATOR_HPP

#include "MazeGenerator.hpp"
#include "Direction.hpp"
#include "Maze.hpp"

#include <vector>

class MyMazeGenerator : public MazeGenerator
{
public:
	MyMazeGenerator();
	virtual void generateMaze(Maze& maze);
	void noVisitedCell(Maze& maze);
	std::vector<Direction> possibleDirections(int row, int col, Maze& maze);
	void makeMaze(int row, int col, Maze& maze);

private:
	std::vector<std::vector<bool>> visited;
};

#endif