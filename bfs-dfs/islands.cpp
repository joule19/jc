#include <iostream>
#include <vector>
#include <queue>

using Matrix = std::vector<std::vector<int>>;

bool inBounds(int newI, int newJ, int rows, int cols)
{
    return newI >= 0 && newI < rows && newJ < cols && newJ >= 0;
}

void expand(Matrix& m, int si, int sj)
{
    int rows = m.size(), cols = m[0].size();

    std::queue<std::pair<int,int>> q;
    q.push({si,sj});

    m[si][sj] = 0;

    while(!q.empty())
    {
        auto [i,j] = q.front();
        q.pop();

        std::vector<std::pair<int,int>> moves = { {-1, 0} , {0, 1} , {1, 0}, {0, -1} };
        for(auto [sx, sy] : moves)
        {
            int newI = i + sx, newJ = j + sy;
            if(inBounds(newI,newJ, rows, cols) && m[newI][newJ] == 1)
                m[newI][newJ] = 0, q.push({newI, newJ});
        }

    }
}

int islandCount(Matrix& m)
{
    int cnt = 0;

    for(int i = 0; i < m.size(); i++)
        for(int j = 0; j < m[0].size(); j++)
            if(m[i][j] == 1)
                cnt++, expand(m, i, j);

    return cnt;
}

int main()
{
    Matrix m = { {0, 0, 0, 1, 0},
                 {0, 1, 0, 1, 0},
                 {0, 1, 1, 0, 0},
                 {1, 0, 0, 1, 0},
                 {1, 0, 0, 0, 1},
                };

    std::cout << islandCount(m) << std::endl;

    return 0;
}