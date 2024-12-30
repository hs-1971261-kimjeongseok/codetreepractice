#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

// TrieNode 클래스 정의
class TrieNode {
public:
    TrieNode* children[26];
    bool is_end;

    TrieNode() : is_end(false) {
        fill(begin(children), end(children), nullptr);
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->is_end = true;
    }

    bool search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                return false;
            }
            node = node->children[index];
        }
        return node->is_end;
    }
};

// DFS 탐색
void dfs(vector<vector<char>>& board, TrieNode* node, int x, int y, string& current_word, vector<vector<bool>>& visited, unordered_set<string>& found_words) {
    static const int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    static const int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

    if (node->is_end) {
        found_words.insert(current_word);
    }

    visited[x][y] = true;

    for (int dir = 0; dir < 8; ++dir) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (nx >= 0 && ny >= 0 && nx < 4 && ny < 4 && !visited[nx][ny]) {
            char next_char = board[nx][ny];
            if (node->children[next_char - 'a']) {
                current_word.push_back(next_char);
                dfs(board, node->children[next_char - 'a'], nx, ny, current_word, visited, found_words);
                current_word.pop_back();
            }
        }
    }

    visited[x][y] = false;
}

int main() {
    int n;
    cin >> n;

    vector<string> words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }

    vector<vector<char>> board(4, vector<char>(4));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> board[i][j];
        }
    }

    // Trie에 단어 삽입
    Trie trie;
    for (const string& word : words) {
        trie.insert(word);
    }

    unordered_set<string> found_words;
    vector<vector<bool>> visited(4, vector<bool>(4, false));

    // 보드판에서 DFS 탐색
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            char start_char = board[i][j];
            if (trie.root->children[start_char - 'a']) {
                string current_word(1, start_char);
                dfs(board, trie.root->children[start_char - 'a'], i, j, current_word, visited, found_words);
            }
        }
    }

    // 가장 긴 단어 길이 출력
    int max_length = 0;
    for (const string& word : found_words) {
        max_length = max(max_length, (int)word.length());
    }

    cout << max_length << endl;

    return 0;
}
