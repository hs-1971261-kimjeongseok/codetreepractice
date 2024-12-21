#include <iostream>
#include <string>
using namespace std;

// 팰린드롬 여부를 확인하는 함수
bool isPalindrome(const string &S, int left, int right) {
    while (left < right) {
        if (S[left] != S[right]) {
            return false;
        }
        ++left;
        --right;
    }
    return true;
}

int main() {
    int n, q;
    cin >> n >> q;
    string S;
    cin >> S;

    while (q--) {
        int a, b;
        cin >> a >> b;
        --a; // 0-based 인덱스로 변환
        --b;

        if (isPalindrome(S, a, b)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
