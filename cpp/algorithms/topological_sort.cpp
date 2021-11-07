#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using Graph = std::vector<std::vector<int>>;

std::vector<bool> seen;
std::vector<int> order;

void rec(const Graph &G, int v) {
    seen[v] = true;
    for (auto next_v : G[v]) {
        if (seen[next_v]) {
            continue;
        }
        rec(G, next_v);
    }

    order.push_back(v);
}

std::string toString(const std::vector<int> a) {
    std::stringstream output;
    std::copy(a.begin(), a.end(), std::ostream_iterator<int>(output, " "));
    return output.str();
}

int main() {
    int N = 5;

    // topological order: 4 2 1 6 3 7 0 5
    Graph G = {
        {5},
        {3, 6},
        {5, 7},
        {0, 7},
        {1, 2, 6},
        {},
        {7},
        {0},
    };
    
    seen.assign(N, false);
    order.clear();

    for (int v = 0; v < N; ++v) {
        if (seen[v]) {
            continue;
        }
        rec(G, v);
    }
    reverse(order.begin(), order.end());

    std::cout << "topological order: " << toString(order) << std::endl;
}

