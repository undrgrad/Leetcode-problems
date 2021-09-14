# Reachable Nodes In Subdivided Graph
## Problem
Given undirected graph with nodes labelled from 0 to n-1. Each edge is subdivided into chain of nodes. Number of nodes in that chain is given along with each edge.
Edges are of the form [u, v, m] where u, v are vertices and m denotes number of nodes in chain. When an edge [u, v, m] is subdivided, it is replaced with m+1 
new edges and m new nodes. Find out how many nodes are reachable from node 0, where a node is reachable if the distance is "maxMoves" or less.

Example 1:  
![Screenshot from 2021-09-14 10-57-39](https://user-images.githubusercontent.com/44015508/133200101-edd66b32-a983-4ae3-b449-d1aaf9c0c5e1.png)

Example 2:
```
Input: edges = [[0,1,4],[1,2,6],[0,2,8],[1,3,1]], maxMoves = 10, n = 4
Output: 23
```
Example 3:
```
Input: edges = [[1,2,4],[1,4,5],[1,3,1],[2,3,4],[3,4,5]], maxMoves = 17, n = 5
Output: 1
Explanation: Node 0 is disconnected from the rest of the graph, so only node 0 is reachable.
```

## Solution
We can use Dikstra's algorithm here. Problem actually reduces to finding each node's shortest distance from node 0 with m as weights of each edge.
For an edge (u,v,m), if we know the maximum value of maxMoves at u and v, then we can visit min(m, maxMoves[u]+maxMoves[v]) chained nodes on edge between u and v.
We can store the edges into a 2d hashtable, so that we can get m between two nodes, i and j, just by e[i][j].  
Note that, here, we want to arrive at a node i with maximum moves left so that we can cover as many nodes on edge (i,j) as possible. For this we are using a priority
queue. Thus, we move greedily and explore the path where we can have maximum moves left.
```c++
int reachableNodes(vector<vector<int>> edges, int M, int N) {
    unordered_map<int, unordered_map<int, int>> e;
    for (auto v : edges) e[v[0]][v[1]] = e[v[1]][v[0]] = v[2];
    priority_queue<pair<int, int>> pq;
    pq.push({M, 0});
    unordered_map<int, int> seen;
    while (pq.size()) {
        int moves = pq.top().first, i = pq.top().second;
        pq.pop();
        if (seen.count(i)) continue;
        seen[i] = moves;
        for (auto j : e[i]) {
            int moves2 = moves - j.second - 1;
            if ((!seen.count(j.first)) && moves2 >= 0)
                pq.push({ moves2, j.first});
        }
    }
    int res = seen.size();
    for (auto v : edges) {
        int a = seen.find(v[0]) == seen.end() ? 0 : seen[v[0]];
        int b = seen.find(v[1]) == seen.end() ? 0 : seen[v[1]];
        res += min(a + b, v[2]);
    }
    return res;
}
```
