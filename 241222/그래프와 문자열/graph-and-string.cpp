#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, char>> edges[100001];
bool visited[100001];

void dfs(int node, string current_path, const string& target, int& count) {
    if (current_path.size() > target.size()) return;
    if (current_path == target) {
        count++;
        return;
    }

    visited[node] = true;
    for (auto edge : edges[node]) {
        int next_node = edge.first;
        if (!visited[next_node]) {
            dfs(next_node, current_path + edge.second, target, count);
        }
    }
    visited[node] = false;
}

int main() {
    int n;
    string p;
    cin >> n >> p;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        edges[a].emplace_back(b, c);
    }

    int count = 0;
    for (int i = 1; i <= n; i++) {
        dfs(i, "", p, count);
    }

    cout << count << endl;
    return 0;
}
