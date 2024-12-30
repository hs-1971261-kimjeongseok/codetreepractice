#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    int prefix_count; // 현재 노드에서 시작하는 접두사의 개수
    bool is_end;      // 현재 노드가 단어의 끝인지 여부

    TrieNode() : prefix_count(0), is_end(false) {
        fill(begin(children), end(children), nullptr);
    }
};

TrieNode* root = new TrieNode();

void InsertWord(const string& word) {
    TrieNode* node = root;
    for (char c : word) {
        int index = c - 'a';
        if (node->children[index] == nullptr) {
            node->children[index] = new TrieNode();
            node->prefix_count++;
        }
        node = node->children[index];
        
    }
    node->is_end = true; // 단어의 끝 표시
}

int FindManualInputs(const string& word) {
    TrieNode* node = root;
    int manual_inputs = 0;

    for (int i = 0; i < word.size(); i++) {
        int index = word[i] - 'a';
        
        
        // 첫 문자는 항상 입력
        if (i == 0 || node->prefix_count > 1 || node->is_end) {
            manual_inputs++;
        }
        node = node->children[index];
    }

    return manual_inputs;
}

int main() {
    int n;
    cin >> n;

    vector<string> words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
        InsertWord(words[i]);
    }

    for (const string& word : words) {
        cout << FindManualInputs(word) << " ";
    }
    cout << endl;

    return 0;
}
