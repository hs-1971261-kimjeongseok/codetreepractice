#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Manacher's Algorithm
vector<int> manacher(const string &s) {
    int n = s.size();
    vector<int> p(n, 0); // p[i]: 팰린드롬 반지름
    int c = 0, r = 0;    // c: 중심, r: 오른쪽 경계

    for (int i = 0; i < n; ++i) {
        if (i < r) {
            p[i] = min(r - i, p[2 * c - i]); // 대칭 위치 이용
        }

        // 팰린드롬 확장
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n && s[i - p[i] - 1] == s[i + p[i] + 1]) {
            ++p[i];
        }

        // 경계 업데이트
        if (i + p[i] > r) {
            c = i;
            r = i + p[i];
        }
    }
    return p;
}

int main() {
    int n, q;
    cin >> n >> q;
    string S;
    cin >> S;

    // 1. 문자열 변환 (홀수, 짝수 팰린드롬 통합 처리)
    string T = "#";
    for (char c : S) {
        T += c;
        T += "#";
    }

    // 2. Manacher's Algorithm으로 팰린드롬 정보 계산
    vector<int> p = manacher(T);

    // 3. 질의 처리
    while (q--) {
        int a, b;
        cin >> a >> b;
        --a; // 0-based 인덱스로 변환
        --b;

        // 변환된 문자열에서 [a, b] 구간이 팰린드롬인지 확인
        int l = 2 * a + 1;               // 시작 위치 (변환 문자열 기준)
        int r = 2 * b + 1;               // 끝 위치 (변환 문자열 기준)
        int mid = (l + r) / 2;           // 중심
        int length = (r - l + 2) / 2;    // 팰린드롬 길이

        if (p[mid] >= length) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
