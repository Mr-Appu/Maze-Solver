#include <bits/stdc++.h>
#include "helper.hpp"

// Time
#include <chrono>

using namespace std;

// Search Algorithms

// Start -> 0 (Left Corner)
// Goal  -> n*n - 1 (Right Corner)

// DFS

void dfs_helper(int node, vector<vector<int>> &graph, vector<int> &vis, vector<int> &path, vector<int> &final_path)
{
    int n = graph.size();

    vis[node] = 1;
    path.push_back(node);

    if(node == n-1) // Target
    {
        final_path.clear(); // There can exist multiple solutions, so store the latest discovered path.
        final_path.assign(path.begin(), path.end()); // Copy : path -> final_path
        return;
    }

    for(auto adj_node: graph[node])
    {
        if(vis[adj_node] == 0) 
        {
            dfs_helper(adj_node, graph, vis, path, final_path);
        }
    }

    // Backtracking
    vis[node] = 0; 
    path.push_back(node);
}

vector<int> dfs(vector<vector<int>> &graph)
{
    int n = graph.size(); // No of Nodes

    vector<int> vis(n, 0);
    vector<int> path, final_path;

    dfs_helper(0, graph, vis, path, final_path);

    return final_path;
}

// BFS

vector<int> bfs(vector<vector<int>> &graph)
{
    int n = graph.size(); // No of Nodes

    queue<int> q;
    vector<int> vis(n, 0);
    vector<int> parent(n, -1); // To track the Path

    q.push(0);
    vis[0] = 1;

    while(!q.empty())
    {
        int node = q.front();
        q.pop();

        if(node == n-1) // Target
        {
            vector<int> path;

            while(node != -1)
            {
                path.push_back(node);
                node = parent[node];
            }
            
            reverse(path.begin(), path.end());
            return path;
        }

        for(int adj_node : graph[node])
        {
            if(!vis[adj_node])
            {
                q.push(adj_node);
                vis[adj_node] = 1;
                parent[adj_node] = node;
            }
        }
    }

    return {}; // No Path
}

signed main(void)
{
    string N = "8";
    string no = "7";

    string file_name = "Maze/" + N  + "x" + N + "/Maze_" + no + ".txt";
    vector<vector<int>> graph = generate_graph(file_name);

    // DFS
    auto start = chrono::high_resolution_clock::now();
    vector<int> path_dfs = dfs(graph); // Serial DFS Function Call
    auto end = chrono::high_resolution_clock::now();

    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
 
    cout << "DFS Path length : " << path_dfs.size() << '\n';
    cout << "Time taken by program is : " << fixed  << time_taken << setprecision(9) << " sec\n";
    display_path(file_name, path_dfs); // Function to Display Maze Path

    // BFS
    start = chrono::high_resolution_clock::now();
    vector<int> path_bfs = bfs(graph); // Serial BFS Function Call
    end = chrono::high_resolution_clock::now();

    time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
 
    cout << "BFS Path length : " << path_bfs.size() << '\n';
    cout << "Time taken by program is : " << fixed  << time_taken << setprecision(9) << " sec\n";
    display_path(file_name, path_bfs); // Function to Display Maze Path
    
    return 0;
}