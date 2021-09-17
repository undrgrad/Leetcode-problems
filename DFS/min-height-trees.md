# Minimum Height Trees
## Problem
Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges where edges[i] = [ai, bi] indicates that there is an undirected edge between the two 
nodes ai and bi in the tree, you can choose any node of the tree as the root. When you select a node x as the root, the result tree has height h. Among all possible 
rooted trees, those with minimum height (i.e. min(h))  are called minimum height trees (MHTs).

Return a list of all MHTs' root labels. You can return the answer in any order.

Examples:

![C1](https://user-images.githubusercontent.com/44015508/133856476-45ff3f79-47c8-45de-97a5-f671b059e91a.JPG)

![C2](https://user-images.githubusercontent.com/44015508/133856483-2c6764a2-abb2-4a16-96be-b67c7e55381e.JPG)

```
n = 7
Edges = [[0,1],[1,2],[1,3],[2,4],[3,5],[4,6]]
Output: [1,2]
```

## Solutions
### Brute Force
We can take each node as root one by one and the tree that we get, we can calculate its height. While doing this, we can maintain minimum height variable for all such
trees.  
```c++
int return_h(int curr, int parent, unordered_map<int, vector<int>> &tree) {
    int h = 0;
    for(auto it: tree[curr]) {
        if(it == parent)    continue;
        h = max(h, return_h(it, curr, tree));
    }
    return  ++h;
}

vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    unordered_map<int, vector<int>> tree;
    for(int i=0 ; i<edges.size() ; i++) {
        int t1 = edges[i][0], t2 = edges[i][1];
        if(tree.find(t1) == tree.end())   tree[t1] = vector<int>();
        tree[t1].push_back(t2);
        if(tree.find(t2-1) == tree.end())   tree[t2] = vector<int>();
        tree[t2].push_back(t1);
    }
    vector<int> ans;
    int minh = INT_MAX;
    for(int i=0 ; i<n ; i++) {
        int ret = return_h(i, -1, tree);
        if(ret < minh) {
            minh = ret;
            ans.clear();
            ans.push_back(i);
        }
        else if(ret == minh) {
            ans.push_back(i);
        }
    }
    return ans;
}
```
But this approach is not efficient.  
Time complexity: O(n^2) where n is the number of nodes.
                 O(n) for calculating height via dfs or bfs
                 O(n) for trying each node
                 

### Inverse BFS
Let's think about a simple case.  
For a path graph of n nodes, find the minimum height trees is trivial. Just designate the middle point(s) as roots.
At each step, we can just prune the leaves from the path graph until we are remaining with 2 or lesser nodes.

Can we extend this to a general tree ?  
Our answer, for a general tree, will lie on the longest path. But finding the longest path in a tree is itself not trivial.
Instead, what we can do is, prune leaf nodes of the tree at each step. Thus, we will be nearing to the middle portion of the longest path in this way.  
We can safely stop when we are left with 2 or lesser nodes.

```c++
vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    // handling base cases
    if(n==1) {
        return vector<int>{0};
    }
    if(n==2) {
        return vector<int>{0,1};
    }
    unordered_map<int, set<int>> G;
    for(int i=0 ; i<edges.size() ; i++) {
        int x = edges[i][0], y = edges[i][1];
        G[x].insert(y);
        G[y].insert(x);
    }
    // Get the initial leaf nodes
    vector<int> leaves;
    for(auto i:G) {
        if(i.second.size() == 1) {
            leaves.push_back(i.first);
        }
    }
    int nodes_left = n;
    //continue until there are more than 2 nodes in the graph
    while(nodes_left > 2) {
        nodes_left -= leaves.size();
        vector<int> int_leaves;
        
        //For all the leaf nodes,
        for(int i=0 ; i<leaves.size() ; i++) {
            int leaf = leaves[i];
            //get the next node in graph
            for(auto nextleaf:G[leaf]) {
                //and disconnect both nodes from each other
                G[nextleaf].erase(leaf);
                G[leaf].erase(nextleaf);
                //If the next (and only) node has become a leaf, then include it as leaf for next step
                if(G[nextleaf].size() == 1)
                    int_leaves.push_back(nextleaf);
            }
        }
        //Continue with new set of leaf nodes after pruning
        leaves = int_leaves;
    }
    sort(leaves.begin(), leaves.end());
    return leaves;
}
```
Here, observe that we inlude any node in leaf set only once. Thus, as an implementation optimization, we don't need to disconnect graph
directly but we can maintain degrees for each node.
```c++
vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    if(n == 1) {
        return {0};
    }
    if(n == 2) {
        return {0, 1};
    }
    //array of vectors
    vector<int> adj[n];
    //to maintain degrees
    vector<int> deg(n, 0);
    for(auto &edge: edges) {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
        deg[edge[0]]++;
        deg[edge[1]]++;
    }
    // using queue and its size to operate on current leaves and add new ones 
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(deg[i] == 1) {
            q.push(i);
        }
    }
    int nodes = n;
    while(nodes > 2) {
        int size = q.size();
        nodes -= size;
        for(int i = 1; i <= size; i++) {
            int u = q.front();
            q.pop();
            //disconnected nodes will have degree 0
            deg[u]--;
            for(auto &x: adj[u]) {
                // this will take place only once
                if(--deg[x] == 1) {
                    q.push(x);
                }
            }
        }
    }
    vector<int> res;
    while(!q.empty()) {
        res.push_back(q.front());
        q.pop();
    }
    return res;
}
```
