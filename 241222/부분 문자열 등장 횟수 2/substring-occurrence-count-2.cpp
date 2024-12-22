#include <iostream>
#include <string>
#include <vector>

#define MAX_N 500000

using namespace std;

// 변수 선언
string T, P;
int n, l;

// 2개의 polynomial rolling 해싱을 위한 p, m 값을 정의합니다.
int p[2] = { 31, 37 };
int m[2] = { int(1e9) + 7, int(1e9) + 9 };

// p^i, 값을 m으로 나눈 나머지를 관리합니다.
long long p_pow[2][MAX_N + 1];

// 소문자 알파벳을 수로 변경합니다.
int ToInt(char c) {
    return c - 'a' + 1;
}

int main() {
    // 입력:
    int m1;
    cin >> T >> m1;
    n = (int)T.size();

    for (int i = 0; i < m1; i++) {
        cin >> P;
        l = (int)P.size();
        int cnt = 0;

        // p_pow 값을 계산합니다.
        for (int k = 0; k < 2; k++) {
            // p_pow[i] = p^i % m
            p_pow[k][0] = 1;
            for (int i = 1; i <= n; i++) {
                p_pow[k][i] = (p_pow[k][i - 1] * p[k]) % m[k];
            }
        }

        // pattern에 대한 해싱값 계산
        long long p_h[2] = {};
        for (int k = 0; k < 2; k++) {
            for (int i = 0; i < l; i++) {
                p_h[k] = (p_h[k] + ToInt(P[i]) * p_pow[k][l - 1 - i]) % m[k];
            }
        }

        // text에서 첫 구간 [0, l - 1]의 해싱값 계산
        long long t_h[2] = {};
        for (int k = 0; k < 2; k++) {
            for (int i = 0; i < l; i++) {
                t_h[k] = (t_h[k] + ToInt(T[i]) * p_pow[k][l - 1 - i]) % m[k];
            }
        }

        // 첫 구간 비교
        if (p_h[0] == t_h[0] && p_h[1] == t_h[1]) {
            cnt++;
        }

        // 이후 구간 탐색
        for (int i = 1; i <= n - l; i++) {
            for (int k = 0; k < 2; k++) {
                // Sliding window로 해싱값 업데이트
                t_h[k] = (t_h[k] * p[k] - ToInt(T[i - 1]) * p_pow[k][l] + ToInt(T[i + l - 1])) % m[k];
                if (t_h[k] < 0) {
                    t_h[k] += m[k];
                }
            }

            // 해싱값 비교
            if (p_h[0] == t_h[0] && p_h[1] == t_h[1]) {
                cnt++;
            }
        }

        // 부분 문자열이 존재하지 않는 경우
        cout << cnt << endl;
    }
    
    return 0;
}
