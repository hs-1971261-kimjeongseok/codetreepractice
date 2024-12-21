#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // 입력 받기
    int n, q;
    cin >> n >> q;
    string S;
    cin >> S;

    // dp 테이블 초기화
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    // 전처리: 길이가 1인 팰린드롬
    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
    }

    // 전처리: 길이가 2인 팰린드롬
    for (int i = 0; i < n - 1; i++) {
        if (S[i] == S[i + 1]) {
            dp[i][i + 1] = true;
        }
    }

    // 전처리: 길이가 3 이상인 팰린드롬
    for (int len = 3; len <= n; len++) { // len: 부분 문자열의 길이
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (S[i] == S[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
            }
        }
    }

    // 질의 처리
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--; // 0-based index로 변환
        b--;
        if (dp[a][b]) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

    return 0;
}
