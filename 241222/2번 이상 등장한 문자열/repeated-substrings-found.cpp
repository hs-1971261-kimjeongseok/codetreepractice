#include <iostream>
#include <string>
#include <unordered_map>

#define MAX_N 500000

using namespace std;

// 2개의 polynomial rolling 해싱을 위한 p, m 값을 정의합니다.
int p[2] = { 31, 37 };
int m[2] = { int(1e9) + 7, int(1e9) + 9 };

// p^i 값을 m으로 나눈 나머지를 관리합니다.
long long p_pow[2][MAX_N + 1];

// 소문자 알파벳을 수로 변경합니다.
int ToInt(char c) {
    return c - 'a' + 1;
}

int main() {
    int l;
    string T;

    // 입력
    cin >> T;
    int n = (int)T.size();

    // p_pow 값을 계산합니다.
    for (int k = 0; k < 2; k++) {
        p_pow[k][0] = 1;
        for (int i = 1; i <= n; i++) {
            p_pow[k][i] = (p_pow[k][i - 1] * p[k]) % m[k];
        }
    }
    int res = 0;
    unordered_map<long long, int> freq;
    int left = 1, right = n, result = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        l = mid;
        // 해싱값을 저장할 map
        bool r = false;

        // 첫 구간 [0, l - 1]의 해싱값 계산
        long long t_h[2] = {};
        for (int k = 0; k < 2; k++) {
            for (int i = 0; i < l; i++) {
                t_h[k] = (t_h[k] + ToInt(T[i]) * p_pow[k][l - 1 - i]) % m[k];
            }
        }

        // 해싱값 결합하여 고유 키 생성
        long long combined_hash = t_h[0] * m[1] + t_h[1];
        if (freq[combined_hash] == 1) { res = l; r = true; }
        freq[combined_hash]++;

        if (!r) {
            // 이후 구간 탐색
            for (int i = 1; i <= n - l; i++) {
                if (r) { break; }
                for (int k = 0; k < 2; k++) {
                    // 슬라이딩 윈도우를 이용한 해싱값 업데이트
                    t_h[k] = (t_h[k] * p[k] - ToInt(T[i - 1]) * p_pow[k][l] + ToInt(T[i + l - 1])) % m[k];
                    if (t_h[k] < 0) {
                        t_h[k] += m[k];
                    }
                }
                // 해싱값 결합하여 고유 키 생성
                combined_hash = t_h[0] * m[1] + t_h[1];
                if (freq[combined_hash] == 1) { res = l; r = true; }
                freq[combined_hash]++;
            }
        }
        if (r) {
            res = mid; // 조건 만족
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    // 결과 출력
    cout << res << endl;
    return 0;
}
