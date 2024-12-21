#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Suffix Array 및 LCP 배열을 계산하는 함수
void suffix_array_and_lcp(const string& S, vector<int>& sa, vector<int>& lcp) {
    int n = S.size();
    vector<int> rank(n), tmp(n), lcp_temp(n);
    
    // 초기화: 첫 번째 단계에서 접미사를 길이 기준으로 정렬
    for (int i = 0; i < n; ++i) {
        sa[i] = i;
        rank[i] = S[i];
    }

    // 접미사 배열 계산
    for (int len = 1; len < n; len *= 2) {
        auto cmp = [&](int i, int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = i + len < n ? rank[i + len] : -1;
            int rj = j + len < n ? rank[j + len] : -1;
            return ri < rj;
        };

        sort(sa.begin(), sa.end(), cmp);

        tmp[sa[0]] = 0;
        for (int i = 1; i < n; ++i) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        rank = tmp;
    }

    // LCP 배열 계산
    for (int i = 0; i < n; ++i) {
        rank[sa[i]] = i;
    }
    
    int h = 0;
    for (int i = 0; i < n; ++i) {
        if (rank[i] > 0) {
            int j = sa[rank[i] - 1];
            while (i + h < n && j + h < n && S[i + h] == S[j + h]) ++h;
            lcp[rank[i]] = h;
            if (h > 0) --h;
        }
    }
}

int main() {
    string S;
    cin >> S;

    int n = S.size();
    vector<int> sa(n), lcp(n);

    // 접미사 배열과 LCP 배열 계산
    suffix_array_and_lcp(S, sa, lcp);

    // 부분 문자열의 총 개수
    long long total_substrings = 0;

    // Suffix Array 기반으로 각 접미사에 포함된 부분 문자열의 개수를 구함
    for (int i = 0; i < n; ++i) {
        total_substrings += n - sa[i] - (i > 0 ? lcp[i] : 0);
    }

    // 결과 출력
    cout << total_substrings << endl;

    return 0;
}
