#include <bits/stdc++.h>

void fastIO() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

bool dfs(int u, std::vector<int> adj[], std::array<int, 100> &match,
         std::array<bool, 100> &visited) {
    for (int v : adj[u]) {
        if (!visited[v]) {
            visited[v] = true;
            if (match[v] == 0 || dfs(match[v], adj, match, visited)) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

void solve() {
    int m, n;
    std::cin >> m >> n;
    int u, v;
    std::vector<int> adj[100];
    std::array<int, 100> match{0};  // 初始化为0
    std::array<bool, 100> visited{};
    
    while (std::cin >> u >> v) {
        if (u == -1 && v == -1)
            break;
        adj[u].push_back(v);
    }

    int matching = 0;
    for (int i = 1; i <= m; i++) {
        visited.fill(false);
        if (dfs(i, adj, match, visited))
            matching++;
    }

    std::cout << matching << std::endl;
    for (int v = m + 1; v <= n; v++) {
        if (match[v] != 0) {
            std::cout << match[v] << " " << v << std::endl;
        }
    }
}

int main() {
    fastIO();
    solve();
    return 0;
}