#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    int prefix_count;

    TrieNode() : prefix_count(0) {
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
        }
        node = node->children[index];
        node->prefix_count++;
    }
}

int FindMaxScore(const string& word) {
    TrieNode* node = root;
    int max_score = 0;
    for (int i = 0; i < word.size(); i++) {
        int index = word[i] - 'a';
        if (node->children[index] == nullptr) {
            break;
        }
        node = node->children[index];
        max_score = max(max_score, (i + 1) * node->prefix_count);
    }
    return max_score;
}

int main() {
    int n;
    cin >> n;

    vector<string> words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
        InsertWord(words[i]);
    }

    int result = 0;
    for (const string& word : words) {
        result = max(result, FindMaxScore(word));
    }

    cout << result << endl;
    return 0;
}
