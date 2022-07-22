#ifndef MYMAZESOLVER_HPP
#define MYMAZESOLVER_HPP

#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"
#include "Direction.hpp"

#include <vector>

class MyMazeSolver : public MazeSolver
{
public:
	MyMazeSolver();
	virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
	void noVisitedCell(const Maze& maze);
	int mazeSolver(const Maze& maze, MazeSolution& mazeSolution);
	std::vector<Direction> possibleDirections(int row, int col, const Maze& maze);

private:
	std::vector<std::vector<bool>> visited;
};

#endif