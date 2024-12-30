#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    int prefix_count;
    int child_count = 0;

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
            node->child_count++;
        }
        node = node->children[index];
        node->prefix_count++;
    }
}

int FindMaxScore(const string& word) {
    TrieNode* node = root;
    int max_score = 1;
    for (int i = 0; i < word.size(); i++) {
        int index = word[i] - 'a';
        if (node->children[index] == nullptr) {
            break;
        }
        if(node->children[index]->child_count != 1 && i != 0){
            max_score++;
        }
        node = node->children[index];
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
        cout << FindMaxScore(word) - 1 << " ";
    }

    //cout << result << endl;
    return 0;
}
