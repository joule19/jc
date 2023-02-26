#include <vector>
#include <queue>
#include <iostream>
#include <tuple>

using Matrix = std::vector<std::vector<int>>;

bool inBounds(int newI, int newJ, int numRows, int numCols)
{
	return newI >= 0 && newI < numRows && newJ < numCols && newJ >= 0;
}

/* Traverse a maze with BFS to find shortest path from (0,0) to (gx,gy) */
int bfs(Matrix& m, int gx, int gy)
{
	int numRows = m.size(), numCols = m[0].size();

	Matrix visited(numRows, std::vector<int>(numCols, 0));

	std::queue<std::tuple<int,int,int>> q;

	q.push( {0,0,0} ); // start in (0,0) with 0 steps

	while(!q.empty())
	{
		auto [i,j,steps] = q.front();
		q.pop();

		if(i == gx && j == gy)
			return steps;

		if(!visited[i][j])
		{
			visited[i][j] = 1;

			std::vector<std::pair<int,int>> moves = {{-1,0}, {0,1}, {1,0}, {0,-1}};

			for(auto [sx,sy] : moves) // check if we can move to each neighbor (newI,newJ) from (i,j)
			{
				int newI = i + sx;
				int newJ = j + sy;                                                     
				if(inBounds(newI,newJ, numRows, numCols) && !m[newI][newJ]  && !visited[newI][newJ])
					q.push({newI, newJ, steps + 1}); 
			}
		}
	}

	return -1;
}

int main()
{
	Matrix m = { {0, 0, 0, 0, 0},
				 {0, 1, 1, 1, 0},
				 {0, 1, 0, 0, 0},
				 {0, 0, 0, 1, 0},
				 {1, 0, 0, 0, 0},
				};
	std::cout << bfs(m, 4, 1) << std::endl;
	return 0;
}