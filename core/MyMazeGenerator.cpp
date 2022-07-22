#include <ics46/factory/DynamicFactory.hpp>

#include "MyMazeGenerator.hpp"
#include <random>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, MyMazeGenerator, "My Algorithm (Required)");

std::random_device device;
std::default_random_engine engine{device()};

MyMazeGenerator::MyMazeGenerator()
{

}


void MyMazeGenerator::generateMaze(Maze& maze)
{
	maze.addAllWalls();
	noVisitedCell(maze);
	makeMaze(0, 0, maze);
}


void MyMazeGenerator::noVisitedCell(Maze& maze)
{
	for (int i = 0; i < maze.getHeight(); i++)
	{
		std::vector<bool> row;
		visited.push_back(row);
		for (int x = 0; x < maze.getWidth(); x++)
			visited[i].push_back(false);
	}
}


std::vector<Direction> MyMazeGenerator::possibleDirections(int row, int col, Maze& maze)
{
	std::vector<Direction> posDir;

	if (col > 0 and visited[row][col-1] == false)
		posDir.push_back(Direction::left);

	if (row > 0 and visited[row-1][col] == false)
		posDir.push_back(Direction::up);

	if (col < (maze.getWidth()-1) and visited[row][col+1] == false)
		posDir.push_back(Direction::right);

	if (row < (maze.getHeight()-1) and visited[row+1][col] == false)
		posDir.push_back(Direction::down);

	return posDir;
}


void MyMazeGenerator::makeMaze(int row, int col, Maze& maze)
{
	visited[row][col] = true;
	std::vector<Direction> posDir = possibleDirections(row, col, maze);
	int dirNum = posDir.size();

	while (dirNum > 0)
	{
		std::uniform_int_distribution<int> distrubution{0, dirNum-1};
		int nextCell = distrubution(engine);

		if (posDir.at(nextCell) == Direction::left)
		{
			maze.removeWall(col, row, Direction::left);
			makeMaze(row, col-1, maze);
		}

		else if (posDir.at(nextCell) == Direction::right)
		{
			maze.removeWall(col, row, Direction::right);
			makeMaze(row, col+1, maze);
		}

		else if (posDir.at(nextCell) == Direction::up)
		{
			maze.removeWall(col, row, Direction::up);
			makeMaze(row-1, col, maze);
		}

		else if (posDir.at(nextCell) == Direction::down)
		{
			maze.removeWall(col, row, Direction::down);
			makeMaze(row+1, col, maze);
		}
		
		posDir = possibleDirections(row, col, maze);
		dirNum = posDir.size();	
	}
}