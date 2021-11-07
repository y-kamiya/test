#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;


// -1: 未探索
// 0: white
// 1: black
std::vector<int> color;

bool dfs(const Graph &G, int v, int cur = 0) {
    std::cout << v << ", color: " << cur << std::endl;
    color[v] = cur;
    for (auto next_v : G[v]) {
        if (color[next_v] != -1) {
            if (color[next_v] == cur) {
                return false;
            }
            continue;
        }

        if (!dfs(G, next_v, 1 - cur)) {
            return false;
        }
    }

    return true;
}

bool isBipartite(const Graph &G, int N) {
    for (int v = 0; v < N; ++v) {
        if (color[v] != -1) {
            continue;
        }

        if (!dfs(G, v)) {
            return false;
        }
    }
    return true;
}

int main() {
    int N = 5;

    Graph G = {
        {1, 3},
        {0, 2, 4},
        {1},
        {0, 4},
        {1, 3},
    };
    
    color.assign(N, -1);

    auto is_bipartite = isBipartite(G, N);

    std::cout << "is_bipartite: " << is_bipartite << std::endl;
}
