#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    int l;
    string s;
    cin >> l >> s;

    unordered_map<string, int> substringCount;
    int n = s.size();
    int maxCount = 0;

    // 슬라이딩 윈도우를 사용해 길이 l의 부분 문자열을 추출
    for (int i = 0; i <= n - l; i++) {
        string sub = s.substr(i, l);
        substringCount[sub]++;
        maxCount = max(maxCount, substringCount[sub]);
    }

    // 가장 많이 등장한 부분 문자열의 등장 횟수 출력
    cout << maxCount << endl;
    return 0;
}
