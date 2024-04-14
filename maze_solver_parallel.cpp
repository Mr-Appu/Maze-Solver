#include <bits/stdc++.h>
#include "helper.hpp"

// OpenMP
#include <omp.h>

// Time
#include <chrono>

using namespace std;

// Start -> 0 (Left Corner)
// Goal  -> n*n - 1 (Right Corner)

// BFS

vector<int> bfs(vector<vector<int>> &graph)
{
    int n = graph.size(); // No of Nodes

    vector<int> q;
    vector<int> vis(n, 0);
    vector<int> parent(n, -1); // To track the Path

    q.push_back(0);
    vis[0] = 1;

    vector<int> path;

    int len = 0;

    while(q.size() != 0)
    {
        vector<int> temp_q;

        #pragma omp parallel for
        for(int i=0; i<q.size(); i++)
        {
            int node = q[i];

            if(node == n-1) // Target
            {
                #pragma omp critical // Critical Section To Avoid Race Condition
                {
                    path.clear();
                    int t_node = node;

                    while(t_node != -1)
                    {
                        path.push_back(t_node);
                        t_node = parent[t_node];
                    }

                    reverse(path.begin(), path.end());
                }
            }

            for(int adj_node : graph[node])
            {
                if(!vis[adj_node])
                {
                    #pragma omp critical // Critical Section To Avoid Race Condition
                    {
                        temp_q.push_back(adj_node);
                        vis[adj_node] = 1;
                        parent[adj_node] = node;
                    }
                }
            }
        }

        q = temp_q;

        if(path.size() != 0) // Path Found
        {
            return path;
        }
    }

    return {}; // No Path
}

void solve(string N, string no, fstream &File)
{
    string file_name = "Maze/" + N  + "x" + N + "/Maze_" + no + ".txt";
    vector<vector<int>> graph = generate_graph(file_name);
 
    // BFS
    auto start = chrono::high_resolution_clock::now();
    vector<int> path_bfs = bfs(graph); // Parallel BFS Function Call
    auto end = chrono::high_resolution_clock::now();

    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    
    File <<  fixed  << time_taken << setprecision(9) << "\n";
}

void report(int p)
{
    for(int i=4; i<=256; i*=2)
    {
        fstream File;
        string file_name = "Report/parallel_" + to_string(p) + "/" + to_string(i) + ".txt";
        File.open(file_name, ios::out);
        
        for(int no=1; no<=10; no++)
        {
            solve(to_string(i), to_string(no), File);
        }
    }

    return;
}

signed main(void)
{
    int p = 1;
    omp_set_num_threads(p);
    
    // report(p);

    string N = "8";
    string no = "1";

    string file_name = "Maze/" + N  + "x" + N + "/Maze_" + no + ".txt";
    vector<vector<int>> graph = generate_graph(file_name);

    // BFS
    auto start = chrono::high_resolution_clock::now();
    vector<int> path_bfs = bfs(graph); // Parallel BFS Function Call
    auto end = chrono::high_resolution_clock::now();

    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
 
    cout << "BFS Path length : " << path_bfs.size() << '\n';
    cout << "Time taken by program is : " << fixed  << time_taken << setprecision(9) << " sec\n";
    display_path(file_name, path_bfs); // Function to Display Maze Path

    return 0;
}