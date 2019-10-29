#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    int mod = 0, sol = 1;
    for (int i = 0; i < n; ++i) {
        mod = (mod * 10 + s[i] - '0') % m;
        if (i == n - 1) {
            if (mod != 0) sol = 0;
        }
        else if (mod == 0)
            sol = sol * 2 % 1000000007;
    }
    cout << sol << endl;
}
