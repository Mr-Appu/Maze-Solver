#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// 0 -> Wall
// 1 -> Path

void display_maze(vector<vector<int>> &arr)
{
    for(auto i : arr)
    {
        for(auto j : i)
        {
            if(j) cout << ".";
            else cout << "#";
        }
        cout << "\n";
    }
}

void shuffle(vector<vector<int>> &arr)
{
    int n = arr.size();

    for(int i=0; i<n; i++)
    {
        int x = rand() % 4;
        int y = rand() % 4;
        
        swap(arr[x], arr[y]);
    }
}

void dfs(int i, int j, vector<vector<int>> &arr)
{
    int n = arr.size();
    int N = (n-1)/2;

    int index_i = 2*i + 1; // index = index in Arr / Map
    int index_j = 2*j + 1;

    vector<vector<int>> dir{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    shuffle(dir);

    // Mark Node as Vis
    arr[index_i][index_j] = 1;

    for(auto next : dir)
    {
        int next_i = i + next[0];
        int next_j = j + next[1];

        if(next_i < 0 || next_i >= N || next_j < 0 || next_j >= N) continue;

        int next_index_i = 2*next_i + 1;
        int next_index_j = 2*next_j + 1;

        if(arr[next_index_i][next_index_j] == 1) continue; // Already Vis

        // Break the Wall for the Path
        int wall_index_i = index_i + next[0];
        int wall_index_j = index_j + next[1];
        arr[wall_index_i][wall_index_j] = 1;

        dfs(next_i, next_j, arr);
    }
}

vector<vector<int>> generate_maze(int N)
{
    // N -> Maze Size

    // n = N + (N + 1)
    // N - No of Cells, N+1 - No of Walls
    int n = 2*N + 1;
    vector<vector<int>> maze(n, vector<int>(n, 0));

    // Generator Maze
    dfs(0, 0, maze);

    return maze;
}

signed main(void)
{
    srand(time(0)); // Random Seed
    
    // // Testing
    // vector<vector<int>> maze = generate_maze(4);   
    // display_maze(maze);
    
    // Generate 10 Maze for each Maze Size
    for(int size=256; size<=256; size*=2)
    {
        for(int i=9; i<=10; i++)
        {
            string path = "Maze/" + to_string(size) + "x" + to_string(size) + "/" + "Maze_" + to_string(i) + ".txt";

            vector<vector<int>> maze = generate_maze(size);

            fstream File;
            File.open(path, ios::out);
            if(!File) continue;
            for(auto temp_i : maze)
            {
                for(auto val : temp_i) File << val;
                File << "\n";
            }
            File.close();
        }
    }

    return 0;
}