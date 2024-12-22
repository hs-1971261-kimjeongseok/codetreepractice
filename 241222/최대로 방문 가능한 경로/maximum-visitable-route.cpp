#include <iostream>
#include <vector>
#include <queue>
#include <climits>

#define MAX_N 100000

using namespace std;

// 변수 선언
int n, m;

vector<int> edges[MAX_N + 1];

// 진입차수를 관리합니다.
int indegree[MAX_N + 1];

// dist[i] : i번 노드까지의 최대 거리
int dist[MAX_N + 1];

// before[i] : i번 노드에서 최대 거리로 이동할 때
// 다음으로 가야할 노드 번호
int before[MAX_N + 1];

// 위상정렬을 위한 큐를 관리합니다.
queue<int> q;

int main() {
    // 입력:
    cin >> n >> m;

    for(int i = 1; i <= m; i++) {
        // 인접리스트로 관리합니다.
        int x, y;
        cin >> x >> y;

        // 사전순으로 가장 앞선 답을 찾기 위해
        // 그래프를 역순으로 만들고, n번 노드에서 1번 노드로 가겠습니다.
        edges[y].push_back(x);
        indegree[x]++; // 진입차수를 갱신합니다.  
    }

    // 모든 거리를 매우 작은 값으로 초기화합니다.
    for(int i = 1; i <= n; i++)
        dist[i] = INT_MIN;

    // n번 노드만 거리를 0으로 해줍니다.
    dist[n] = 0;

    // 처음 indegree 값이 0인 곳이 시작점이 됩니다.
    // 이 노드들을 queue에 넣어줍니다.
    for(int i = 1; i <= n; i++)
        if(!indegree[i]) {
            q.push(i);
        }
    
    // 위상정렬을 진행합니다.
    // queue에 원소가 남아있다면 계속 진행합니다.
    while(!q.empty()) {
        // 가장 앞에 있는 원소를 뽑아줍니다.
        int x = q.front();
        q.pop();
        
        // x에서 갈 수 있는 모든 곳을 탐색합니다.
        for(int i = 0; i < (int) edges[x].size(); i++) {
            int y = edges[x][i];

            // dist 정보를 갱신합니다.
            if(dist[x] != INT_MIN) {
                if(dist[y] < dist[x] + 1) {
                    dist[y] = dist[x] + 1;
                    before[y] = x;
                }
                // 값이 동일한 경우에는 
                // 추후 사전순으로 앞선 답을 만들어주기 위해 더 작은 값을 넣어줍니다.
                else if(dist[y] == dist[x] + 1 && before[y] > x) {
                    before[y] = x;
                }
            }

            // 해당 노드의 indegree를 1만큼 감소시켜줍니다.
            indegree[y]--;

            // 비로소 indegree가 0이 되었다면
            // queue에 새로 넣어줍니다.
            if(!indegree[y]) {
                q.push(y);
            }
        }
    }

    // dist[1]에 값이 들어가 있지 않다면,
    // 1번 노드에서 n번 노드로 가는 길이 없습니다.
    if(dist[1] == INT_MIN) {
        cout << -1;
        return 0;
    }

    // 1번 노드에서부터 before을 타고 가
    // n번 노드까지 경로를 저장합니다.
    vector<int> ans;
    int cur = 1;
    ans.push_back(cur);
    while(cur != n) {
        cur = before[cur];
        ans.push_back(cur);
    }

    // 정답과 경로를 출력합니다.
    cout << ans.size() << endl;
    for(int i = 0; i < (int) ans.size(); i++)
        cout << ans[i] << " ";

    return 0;
}