#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1); // 인접 리스트
    vector<int> indegree(n + 1, 0); // 진입 차수
    vector<int> dp(n + 1, -1); // 최장 경로 길이
    vector<int> parent(n + 1, -1); // 경로 역추적을 위한 부모 정보

    // 간선 정보 입력
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        indegree[y]++;
    }

    // 사전순 보장을 위해 인접 리스트 정렬
    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    // 위상 정렬 준비 (사전순으로 처리)
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            pq.push(i);
        }
    }

    // 위상 정렬 수행
    vector<int> topoOrder;
    while (!pq.empty()) {
        int curr = pq.top();
        pq.pop();
        topoOrder.push_back(curr);

        for (int next : adj[curr]) {
            indegree[next]--;
            if (indegree[next] == 0) {
                pq.push(next);
            }
        }
    }

    // 시작점 초기화
    dp[1] = 1;

    // DP로 최장 경로 계산
    for (int node : topoOrder) {
        if (dp[node] == -1) continue; // 도달하지 못한 노드는 무시
        for (int next : adj[node]) {
            if (dp[next] < dp[node] + 1) {
                dp[next] = dp[node] + 1;
                parent[next] = node;
            }
        }
    }

    // 결과 출력
    if (dp[n] == -1) {
        cout << -1 << endl; // n번 노드에 도달할 수 없음
        return 0;
    }

    // 최대 경로 길이 출력
    cout << dp[n] << endl;

    // 경로 복원
    vector<int> path;
    for (int curr = n; curr != -1; curr = parent[curr]) {
        path.push_back(curr);
    }
    reverse(path.begin(), path.end());

    // 경로 출력
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
