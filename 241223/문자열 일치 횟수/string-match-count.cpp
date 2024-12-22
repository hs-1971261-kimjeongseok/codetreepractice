#include <iostream>
#include <string>
#include <vector>

using namespace std;

// KMP failure function을 계산하는 함수
vector<int> computeFailureFunction(const string &pattern) {
    int m = pattern.size();
    vector<int> f(m, 0);
    int j = 0;

    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j])
            j = f[j - 1];
        if (pattern[i] == pattern[j])
            j++;
        f[i] = j;
    }
    return f;
}

// KMP 알고리즘을 이용해 문자열 매칭 횟수를 구하는 함수
int countMatches(const string &text, const string &pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> f = computeFailureFunction(pattern);

    int j = 0, count = 0;

    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j])
            j = f[j - 1];
        if (text[i] == pattern[j])
            j++;
        if (j == m) {
            count++;
            j = f[j - 1];
        }
    }
    return count;
}

int main() {
    int n;
    string T, P;

    // 입력 받기
    cin >> n >> T >> P;

    // 문자열 P를 두 번 붙여서 shift 효과를 얻음
    string shiftedPattern = P + P;
    string text = T;

    // P 길이만큼의 부분 문자열만 고려
    shiftedPattern = shiftedPattern.substr(0, P.size() + n - 1);

    // 문자열 매칭 횟수 계산
    int result = countMatches(shiftedPattern, T);

    cout << result << endl;

    return 0;
}
