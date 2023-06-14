#include<bits/stdc++.h>
using namespace std;

// bfs:  i) Push the startNode and mark it as visited
//      ii) In while loop pop the front node and add the child nodes into queue
//          if they are not visited and while adding into queue mark the child node as visited.

// dfs:   i) Recursion stack is used not external stack, mark the current node as visited
//       ii) Call the dfs on all the child nodes if it is not visited.

void graphImplementatio() {

    // adjacency list   i)  vector<int> graph[n];    graph is an array n vectors;
    // vector< list<int> > graph(n);   It is best to use as insertion is fast in list data structure
    // unordered_map<int, list<int>> graph;  first param can be anything (char, int etc) and second is list of edges

    // for weighted graph adjacency list is  vector<pair<int, int>> graph[n];   in the pair store dest node, weight

    int n, m;
    cin >> n >> m;  // n is no.of nodes and m is no.of edges
    vector<list<int>> graph;

    for (int i=0; i<m; i++) {

        int u,v;
        cin >> u >> v;

        // if it is undirected store it in both map[u] and map[v]
        // if it is directed store it in map[u]  ( u to v there is edge)

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // printing the graph
    for (int i=0; i<n; i++) {
        cout << i << " ->  ";   // node number
        for (auto child: graph[i])
            cout << child << " ";
        cout << endl;
    }
}

//  On startNode recursively call the dfs on every child only if it is not visited
void dfs(vector<int> adj[], vector<bool> &visited, vector<int> &ans, int startNode) {
    
    // Region 1:  Just entered the node 
    //            so after seeing the vertex mark as visited
    visited[startNode] = true;
    ans.push_back(startNode);

    for (int child: adj[startNode]) {   

        // Region 2:  Entering every child of startNode
        if (!visited[child]) {
            dfs(adj, visited, ans, child);
        }
        // Region 3:  Exit of every child of startNode and return to startNode
    }

    // Region 4:  Exit of startNode and return the parent of startNode
}

vector<int> dfsOfGraph(int V, vector<int> adj[]) {

    // dfs on disconnected graph apply on every vertex which is not visited
    // Time complexity : O(V+2E) In worst case travel all nodes and for every node travel it's child (sum of deg)

    vector<bool> visited(V, false);
    vector<int> ans;
    for (int i=0; i<V; i++) {       // dfs cover entire connected component if called
        dfs(adj, visited, ans, i);
    }

    return ans;
}

void bfsOnComponent(vector<list<int>> &graph, vector<int> &ans, vector<bool> &visited, int startNode) {

    // mark the node as visited when it is pushed into the queue
    queue<int> q;
    visited[startNode] = true;  // first mark the start node as visited and then push the node into the queue
    q.push(startNode);
    while (!q.empty()) {

        int frontNode = q.front();
        ans.push_back(frontNode);
        q.pop();
        for (auto node: graph[frontNode]) {
            if (!visited[node])  {              
                visited[node] = true;
                q.push(node);
            }
        }
    }
}

void BFS()  {

    // BFS for disconnected components
    // Time complexity: O(n + 2e)  Every node goes into the queue once and runs for all it's adjacent edges (degree times)
    //                  So time comp is sum of all degree ele i.e  2E and n for every element push in queue
    // Space complexity: O(n+n+n)  i.e auxilary for visited, queue, ans for storing 

    int n, m;
    vector<list<int>> graph;
    vector<bool> visited(n, false);
    vector<int> ans;

    for (int i=0; i<n; i++) {   // if it is not visited then it is other component apply bfs again
        if (!visited[i])
            bfsOnComponent(graph, ans, visited, i);
    }
}

void bfsOnIsland(int row, int col, vector<vector<bool>> &visited, vector<vector<char>> &grid) {
    
    queue<pair<int, int>> q;
    q.push({row, col});
    visited[row][col] = true;
    int m = grid.size(),  n = grid[0].size();
    
    int arr[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    while (!q.empty()) {
        
        int row = q.front().first;
        int col = q.front().second;
        q.pop();
        
        for (int i=0; i<4; i++) {
            int nrow = arr[i][0] + row;
            int ncol = arr[i][1] + col;
            
            if (nrow >= 0 && ncol >= 0 && nrow < m && ncol < n &&
                !visited[nrow][ncol] && grid[nrow][ncol] == '1') {
                
                visited[nrow][ncol] = true;
                q.push({nrow, ncol});
            }
        }
    }
    
}

 void dfsOnIsland(int row, int col, vector<vector<char>> &grid, vector<vector<int>> &visited) {
        
    visited[row][col] = true;   // mark the current nodes as visited
    int m = grid.size(),  n = grid[0].size();
    int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    for (int i=0; i<4; i++) {          // call the function on it's children
        int nrow = row + dir[i][0];
        int ncol = col + dir[i][1];
        
        if (nrow >= 0 && nrow < m && ncol >= 0 && ncol < n           // check the boundary and visited or not
            && !visited[nrow][ncol] && grid[nrow][ncol] == '1') {     // not visited means call the fun on child
                
                dfsOnIsland(nrow, ncol, grid, visited);
        }
    }
}

int numIslands(vector<vector<char>>& grid) {
    
    int m = grid.size(),  n = grid[0].size(),  count = 0;
    vector<vector<bool>> visited (m,  vector<bool>(n, false));
    
    for (int row=0; row<m; row++) {
        
        for (int col=0; col<n; col++) {
            if (!visited[row][col] && grid[row][col] == '1') {
                ++count;
                bfsOnIsland(row, col, visited, grid);
            }
        }
    }
    return count;
}

int bfs(vector<vector<int>> &grid,  vector<vector<bool>> &visited,  queue < pair< pair<int, int>, int> > &q) {
        
    int maxTime = 0,  m = grid.size(),  n = grid[0].size();
    while (!q.empty()) {
        
        int row = q.front().first.first;
        int col = q.front().first.second;
        int timeStamp = q.front().second;
        q.pop();     // read the front element and then pop it.
        
        int dir[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
        
        for (int i=0; i<4; i++) {     // check all 4 directions
            
            int nrow = row + dir[i][0];  
            int ncol = col + dir[i][1];
            
            if (nrow >= 0 && nrow < m && ncol >= 0 && ncol < n            // boundary condt for neighbour elements
                    && !visited[nrow][ncol] && grid[nrow][ncol] == 1) {  // visited or not , orange fresh or not
                
                q.push({ {nrow, ncol}, timeStamp+1 });       // if it is true push the row, col, time + 1 
                grid[nrow][ncol] = 2;                        // rotten it
                visited[nrow][ncol] = true;                  // mark as visted
                maxTime = timeStamp + 1;                    // maintain max time stamp
            }
        }
    }

    return maxTime;
}

int orangesRotting(vector<vector<int>>& grid) {
    
    int m = grid.size(),  n = grid[0].size();
    vector<vector<bool>> visited (m,  vector<bool> (n, false));
    queue < pair< pair<int, int>, int> > q;  // pair of pair and int inner pair contains row, col and second is time
    
    for (int row=0; row<m; row++) {
        
        for (int col=0; col<n; col++) {
            
            if (grid[row][col] == 2) {
                q.push({{row, col}, 0});    // for given row, col timeStamp is 0
                visited[row][col] = true;   // mark as visited
            }
        }
    }
    
    int res = bfs(grid, visited, q);        // for all the starting nodes parallel execution of bfs will be done

    for (int row = 0; row < m; row++) {
        
        for (int col = 0; col < n; col++) {
            
            if (grid[row][col] == 1)  // check if still 1's present
                return -1;
        }
    }
    
    return res;
}
