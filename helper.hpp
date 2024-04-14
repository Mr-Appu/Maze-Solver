#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// 0 -> Wall
// 1 -> Path

// Helper Functions

// Returns Number of Lines in a File
int file_length(string file_name) 
{
    fstream File;
    File.open(file_name, ios::in);

    int lines = 0; // File Length
    string line;

    for(lines = 0; std::getline(File,line); lines++);

    return lines;
}

// Converts a Text FIle to an Array
vector<vector<int>> read_maze(string file_name)
{

    fstream File;
    File.open(file_name, ios::in);

    int n = file_length(file_name); // Cells
    int N = (n - 1) / 2; // Nodes 

    vector<vector<int>> maze(n, vector<int>(n, -1));
    
    for(int i=0; i<n; i++)
    {
        string str; File >> str;

        for(int k=0; k<n; k++) maze[i][k] = str[k] - '0';
    }

    return maze;
}

// Converts an Array to a Graph
vector<vector<int>> generate_graph(string file_name)
{
    vector<vector<int>> maze = read_maze(file_name);

    int n = maze.size(); // Cells
    int N = (n - 1) / 2; // Nodes

    vector<vector<int>> graph(N*N);

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            int node = N*i + j;

            int index_i = 2*i + 1;
            int index_j = 2*j + 1;

            vector<vector<int>> dir {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

            for(int k=0; k<4; k++)
            {
                if(maze[index_i + dir[k][0]][index_j + dir[k][1]]) // Check Neighborhood walls
                {
                    int n_node = N*(i + dir[k][0]) + (j + dir[k][1]); // Neighborhood Node

                    graph[node].push_back(n_node);
                }
            }
        }
    }

    return graph;
}

// Given a Path and File Name, Plots the path in 2D Space
void display_path(string file_name, vector<int> &path)
{
    int n = file_length(file_name); // No of Cells (4x4) - 9
    int N = (n - 1) / 2; // No of Nodes (4x4) - 4

    vector<vector<int>> maze(n, vector<int> (n, 0));

    for(auto node : path)
    {
        int i = (node / N);
        int j = (node % N);

        int index_i = 2*i + 1;
        int index_j = 2*j + 1;

        maze[index_i][index_j] = 1;
    }

    for(int k=0; k<path.size()-1; k++)
    {
        int cur_node = path[k];
        int nxt_node = path[k+1];

        int cur_i = 2*(cur_node / N) + 1;
        int cur_j = 2*(cur_node % N) + 1;

        int nxt_i = 2*(nxt_node / N) + 1;
        int nxt_j = 2*(nxt_node % N) + 1;

        int dif_i = (nxt_i - cur_i) / 2;
        int dif_j = (nxt_j - cur_j) / 2;

        maze[cur_i + dif_i][cur_j + dif_j] = 1;
    }

    for(auto row : maze)
    {
        for(auto cell : row)
        {
            if(cell) cout << "*";
            else cout << ".";
        }
        cout << "\n";
    }
}