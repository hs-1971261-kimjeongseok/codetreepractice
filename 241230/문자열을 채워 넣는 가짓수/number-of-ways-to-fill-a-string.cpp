#include <iostream>
#include <string>

#define MAX_N 5000
#define MAX_M 100000

const int MOD = 1e9 + 7;

using namespace std;

// 변수 선언
int n, m;
string defaultString;
string words[MAX_M];
int dp[MAX_N + 1];

// Trie에 사용되는 노드를 정의합니다.
class TrieNode {
    public:
        // 각 노드에는 'a'부터 'z'까지의 문자에 대응되는 26개의 노드 정보가 관리됩니다.
        TrieNode *children[26];

        // 해당 노드를 기점으로 하나의 단어가 완성되는지를 판단합니다.
        bool is_end;

        // 생성자입니다.
        TrieNode() {
            // 단어 완성에 대한 초기값은 false입니다.
            is_end = false;

            // 각 문자에 대응되는 노드 정보는 처음에 nullptr이 됩니다.
            for(int i = 0; i < 26; i++)
                children[i] = nullptr;
        }
};

// 루트 노드에 해당하는 TrieNode를 처음 만들어줍니다.
TrieNode *root = new TrieNode();

// 단어 s를 Trie에 넣어줍니다.
void InsertWord(string s) {
    // root에서 시작합니다.
    TrieNode *t = root;

    for(int i = 0; i < (int) s.size(); i++) {
        // 문자 순서대로 따라가면 됩니다.
        // 'a'부터 'z'까지 사용되므로
        // 각각을 A(0)부터 Z(25)까지의 index로 매핑시켜줍니다.
        int index = s[i] - 'a';
        // 해당하는 노드가 아직 없다면 새로운 노드를 만들어줍니다.
        if(t->children[index] == nullptr) {
            t->children[index] = new TrieNode();
        }
        
        // index에 해당하는 노드로 옮겨갑니다.
        t = t->children[index];
    }

    // 최종 위치에 단어의 끝임을 표시해줍니다.
    t->is_end = true;
}

// idx번째 dp를 갱신해줍니다.
void updateDP(string &s, int idx) {
    // root에서 시작합니다.
    TrieNode *t = root;

    for(int i = idx; i < s.length(); i++) {
        // 해당하는 노드를 계속 따라갑니다.
        int index = s[i] - 'a';

        t = t->children[index];

        // 만족하는 트라이가 없다면 멈춥니다.
        if(!t) break;

        // 해당 위치에 문자열이 존재한다면
        // dp값을 갱신해줍니다.
        if(t -> is_end) {
            dp[i + 1] += dp[idx];
            dp[i + 1] %= MOD;
        }
    }
}

int main() {
    // 입력:
    cin >> defaultString >> m;
    for(int i = 0; i < m; i++) {
        cin >> words[i];
    }
    n = defaultString.length();

    // Trie에 단어들을 넣어줍니다.
    for(int i = 0; i < m; i++)
        InsertWord(words[i]);

    dp[0] = 1;

    // 순서대로 한칸씩 이동하면서 dp를 갱신해줍니다.
    for(int i = 0; i < n; i++) {
        updateDP(defaultString, i);
    }

    cout << dp[n];

    return 0;
}