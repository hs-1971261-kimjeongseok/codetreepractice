#include <iostream>
#include <string>

using namespace std;

// 변수 선언
int n = 6;
string words[10000];

// Trie에 사용되는 노드를 정의합니다.
class TrieNode {
public:
    TrieNode* parent;
    // 각 노드에는 'a'부터 'z'까지의 문자에 대응되는 26개의 노드 정보가 관리됩니다.
    TrieNode* children[10];
    // 해당 노드를 기점으로 하나의 단어가 완성되는지를 판단합니다.
    bool is_end;
    int cnt;

    // 생성자입니다.
    TrieNode() {
        // 단어 완성에 대한 초기값은 false입니다.
        is_end = false;

        cnt = 0;

        // 각 문자에 대응되는 노드 정보는 처음에 nullptr이 됩니다.
        for (int i = 0; i < 10; i++)
            children[i] = nullptr;
    }
};

// 루트 노드에 해당하는 TrieNode를 처음 만들어줍니다.
TrieNode* root = new TrieNode();

// 단어 s를 Trie에 넣어줍니다.
void InsertWord(string s) {
    // root에서 시작합니다.
    TrieNode* t = root;
    for (int i = 0; i < (int)s.size(); i++) {
        // 문자 순서대로 따라가면 됩니다.
        // 'a'부터 'z'까지 사용되므로
        // 각각을 0부터 25까지의 index로 매핑시켜줍니다.
        int index = s[i] - '0';
        // 해당하는 노드가 아직 없다면 새로운 노드를 만들어줍니다.
        if (t->children[index] == nullptr) {
            t->children[index] = new TrieNode();
            t->children[index]->parent = t;
            t->children[index]->cnt = t->cnt;
        }

        // index에 해당하는 노드로 옮겨갑니다.
        t = t->children[index];
    }
    // 최종 위치에 단어의 끝임을 표시해줍니다.
    t->is_end = true; t->cnt++;
}

bool FindWord(string s) {
    TrieNode* t = root;
    for (int i = 0; i < (int)s.size(); i++) {

        int index = s[i] - '0';
        t = t->children[index];
    }

    return t->cnt >= 2;
}

int main() {
    int a; cin >> a;

    // Trie에 단어들을 넣어줍니다.
    for (int i = 0; i < n; i++) {
        cin >> words[i];
        InsertWord(words[i]);
    }
    bool exist = false;
    for (int i = 0; i < n; i++) {
        if (FindWord(words[i])) {
            exist = true;
            break;
        }
    }
    if (exist) { cout << 0; }
    else { cout << 1; }
    return 0;
}
