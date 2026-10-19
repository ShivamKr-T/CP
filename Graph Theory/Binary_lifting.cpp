#include<bits/stdc++.h>
using namespace std;

const int LOG=20;
const int N=3e5+9;

vector<vector<int>> adj(N);
int up[N][LOG], depth[N], sz[N];

void dfs(int node, int par = 0) {
    up[node][0] = par;
    depth[node] = depth[par] + 1;
    // sz[u] = 1;
    for (int i = 1; i < LOG; i++) up[node][i] = up[up[node][i - 1]][i - 1];
    for (int c: adj[node]){
        if(c==par) continue;
        dfs(c, node);
        // sz[u] += sz[v];
    }
}
// TC: O(N*LOG)

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int k=depth[u]-depth[v];
    for(int i = LOG-1; i >= 0; i--){
        if(k&(1ll<<i)) u=up[u][i];
    }
    if (u == v) return u;
    for (int i = LOG-1; i >= 0; i--){
        if (up[u][i] != up[v][i]) u = up[u][i], v = up[v][i];
    } 
    return up[u][0];
}
// TC: O(LOG)

int kth(int u, int k) {
    assert(k >= 0);
    for (int i = 0; i < LOG; i++) if (k & (1 << i)) u = up[u][i];
    return u;
}
// TC: O(LOG)

int dist(int u, int v) {
    int l = lca(u, v);
    return depth[u] + depth[v] - (depth[l] << 1);
}
// TC: O(LOG)

// kth node from u to v, 0th node is u
int go(int u, int v, int k) {
    int l = lca(u, v);
    int d = depth[u] + depth[v] - (depth[l] << 1);
    assert(k <= d);
    if (depth[l] + k <= depth[u]) return kth(u, k);
    k -= depth[u] - depth[l];
    return kth(v, depth[v] - depth[l] - k);
}
// TC: O(LOG)


// Questions: 
// https://leetcode.com/problems/kth-ancestor-of-a-tree-node/description/ (LC 1483) [Easy]
// https://www.codechef.com/problems/CATS [Med]
// https://www.codechef.com/problems/UPDOTR [Med]
// https://www.codechef.com/problems/LGSEG [Med]
