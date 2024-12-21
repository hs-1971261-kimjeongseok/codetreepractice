#include <iostream>
#include <string>
#include <unordered_set>
#define MAX_N 5000

using namespace std;

// 2개의 polynomial rolling 해싱을 위한 p, m 값을 정의합니다.
int p[2] = {31, 37};
int m[2] = {int(1e9) + 7, int(1e9) + 9};

// p^i 값을 m으로 나눈 나머지를 관리합니다.
long long p_pow[2][MAX_N + 1];

// 소문자 알파벳을 수로 변경합니다.
int ToInt(char c) {
    return c - 'a' + 1;
}

int main() {
    string S;
    cin >> S;
    int n = (int)S.size();

    // p_pow 값을 계산합니다.
    for (int k = 0; k < 2; k++) {
        p_pow[k][0] = 1;
        for (int i = 1; i <= n; i++) {
            p_pow[k][i] = (p_pow[k][i - 1] * p[k]) % m[k];
        }
    }

    // 서로 다른 해싱값을 저장할 집합
    unordered_set<long long> unique_hashes;

    // 부분 문자열 길이를 1부터 n까지 확장
    for (int len = 1; len <= n; len++) {
        long long t_h[2] = {};

        // 첫 구간 [0, len - 1]의 해싱값 계산
        for (int k = 0; k < 2; k++) {
            for (int i = 0; i < len; i++) {
                t_h[k] = (t_h[k] + ToInt(S[i]) * p_pow[k][len - 1 - i]) % m[k];
            }
        }

        // 첫 구간의 해싱값을 추가
        long long combined_hash = t_h[0] * m[1] + t_h[1];
        unique_hashes.insert(combined_hash);

        // 이후 구간 탐색
        for (int i = 1; i <= n - len; i++) {
            for (int k = 0; k < 2; k++) {
                // 슬라이딩 윈도우를 이용한 해싱값 업데이트
                t_h[k] = (t_h[k] * p[k] - ToInt(S[i - 1]) * p_pow[k][len] + ToInt(S[i + len - 1])) % m[k];
                if (t_h[k] < 0) {
                    t_h[k] += m[k];
                }
            }

            // 해싱값 결합하여 고유 키 생성
            combined_hash = t_h[0] * m[1] + t_h[1];
            unique_hashes.insert(combined_hash);
        }
    }

    // 서로 다른 부분 문자열의 개수 출력
    cout << unique_hashes.size() << endl;

    return 0;
}
