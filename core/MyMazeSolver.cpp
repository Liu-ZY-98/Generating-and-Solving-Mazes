#include <ics46/factory/DynamicFactory.hpp>

#include "MyMazeSolver.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, MyMazeSolver, "My Maze Solver (Required)");

MyMazeSolver::MyMazeSolver()
{

}


void MyMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
	mazeSolution.restart();
	noVisitedCell(maze);
	mazeSolver(maze, mazeSolution);
}


void MyMazeSolver::noVisitedCell(const Maze& maze)
{
	for (int i = 0; i < maze.getHeight(); i++)
	{
		std::vector<bool> row;
		visited.push_back(row);
		for (int x = 0; x < maze.getWidth(); x++)
			visited[i].push_back(false);
	}
}

std::vector<Direction> MyMazeSolver::possibleDirections(int row, int col, const Maze& maze)
{
	std::vector<Direction> posDir;

	if (col > 0 and visited[row][col-1] == false and maze.wallExists(col, row, Direction::left) == false)
		posDir.push_back(Direction::left);

	if (row > 0 and visited[row-1][col] == false and maze.wallExists(col, row, Direction::up) == false)
		posDir.push_back(Direction::up);

	if (col < (maze.getWidth()-1) and visited[row][col+1] == false and maze.wallExists(col, row, Direction::right) == false)
		posDir.push_back(Direction::right);

	if (row < (maze.getHeight()-1) and visited[row+1][col] == false and maze.wallExists(col, row, Direction::down) == false)
		posDir.push_back(Direction::down);

	return posDir;
}

int MyMazeSolver::mazeSolver(const Maze& maze, MazeSolution& mazeSolution)
{
	int col = mazeSolution.getCurrentCell().first;
	int row = mazeSolution.getCurrentCell().second;

	visited[row][col] = true;


	if (mazeSolution.isComplete() == true)
	{
		return 1;
	}

	if ((maze.wallExists(col, row, Direction::left) == false) and (visited[row][col-1] == false))
	{
		mazeSolution.extend(Direction::left);
		int pathEnd = mazeSolver(maze, mazeSolution);

		if (pathEnd == 1 and mazeSolution.isComplete() == false)
			mazeSolution.backUp();
		else
			return 0;
	}

	if ((maze.wallExists(col, row, Direction::right) == false) and (visited[row][col+1] == false))
	{
		mazeSolution.extend(Direction::right);
		int pathEnd = mazeSolver(maze, mazeSolution);

		if (pathEnd == 1 and mazeSolution.isComplete() == false)
			mazeSolution.backUp();
		else
			return 0;
	}
	
	if ((maze.wallExists(col, row, Direction::up) == false) and (visited[row-1][col] == false))
	{
		mazeSolution.extend(Direction::up);
		int pathEnd = mazeSolver(maze, mazeSolution);

		if (pathEnd == 1 and mazeSolution.isComplete() == false)
			mazeSolution.backUp();
		else
			return 0;
	}

	if ((maze.wallExists(col, row, Direction::down) == false) and (visited[row+1][col] == false))
	{
		mazeSolution.extend(Direction::down);
		int pathEnd = mazeSolver(maze, mazeSolution);

		if (pathEnd == 1 and mazeSolution.isComplete() == false)
			mazeSolution.backUp();
		else
			return 0;
	}

	return 1;
}
