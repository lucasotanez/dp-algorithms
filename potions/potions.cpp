#include <vector>
#include <iostream>
#include <limits.h>
#include <algorithm>

// WORK IN PROGRESS

using namespace std;

int solve(vector<int> a, vector<int>b, vector<int> c, int Ma, int Mb);

bool ratio(int a1, int b1, int a2, int b2);

int main() {
    vector<int> costs = {3, 2, 1, 5, 8};
    vector<int> powderA = {1, 3, 2, 3, 4};
    vector<int> powderB = {2, 6, 1, 2, 5};
    int Ma = 1;
    int Mb = 3;

    cout << solve(powderA, powderB, costs, Ma, Mb) << endl;

}

int solve(vector<int> a, vector<int>b, vector<int> c, int Ma, int Mb) {
    int n = a.size();

    int aTotal = 0;
    int bTotal = 0;

    for (int i = 0; i < n; i++) {
        aTotal += a[i];
        bTotal += b[i];
    }

    vector<vector<vector<int>>> MP(n+1, (vector<vector<int>> (aTotal+1, vector<int> (bTotal+1, 100000))));

    for (int i = 0; i < n; i++) {
        MP[i][0][0] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= aTotal; j++) {
            for (int k = 1; k <= bTotal; k++) {
                MP[i][j][k] = MP[i-1][j][k];
                // FIX:
                // These indices are all fucked
                if ((j-a[i-1] >= 0) && (k-b[i-1] >= 0)) {
                    if ((MP[i-1][j-a[i-1]][k-b[i-1]] + c[i-1]) < MP[i][j][k]) {
                        MP[i][j][k] = (MP[i-1][j-a[i-1]][k-b[i-1]] + c[i-1]);
                    }
                }
            }
        }
    }

    int minCost = 100000;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= aTotal; j++) {
            for (int k = 1; k <= bTotal; k++) {
                if (ratio(j, k, Ma, Mb)) {
                    minCost = min(minCost, MP[i][j][k]);
                }
            }
        }
    }

    if (minCost == 100000) return -1; // not possible
    else return minCost;
}

bool ratio(int a1, int b1, int a2, int b2) {
    return (a1 * b2) == (b1 * a2);
}
