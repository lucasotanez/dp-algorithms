#include <vector>
#include <iostream>
#include <algorithm>

/* ================================== OVERVIEW ========================================

In order to make a Magic Potion, one needs to mix powder A and powder B in the ratio
of Ma : Mb. A pharmacy sells n bottles, where bottle i costs c_i, contains a_i grams of
powder A, and b_i grams of powder B. Provided that you MUST use ALL the powder you buy, 
determine the minumum budget needed to construct the potion, or assert that no such 
formulation exists. Assume Ma, Mb, a_i, and b_i are all integers.

Recursively,
MP(i, a, b) = minimum cost of forming the ratio a : b using up to i potions

Base cases:
1. MP(i, 0, 0) = 0

*/

using namespace std;

// DP logic
int solve(vector<int> a, vector<int>b, vector<int> c, int Ma, int Mb);

// helper ratio equivalence checker (O(1))
bool ratio(int a1, int b1, int a2, int b2);

int main() {
    // cost could be floats instead... algorithm will still work
    vector<int> costs = {4, 2, 1, 5, 8};
    // powders (ratios) need to integers
    vector<int> powderA = {1, 2, 3, 2, 4};
    vector<int> powderB = {6, 1, 2, 3, 5};
    int Ma = 1;
    int Mb = 3;

    int result = solve(powderA, powderB, costs, Ma, Mb);
    if (result == -1) {
        cout << "A Magic Potion with ratio " << Ma << ":" << Mb <<
            " cannot be constructed from this set of potions." << endl;
    } else {
        cout << "The minimum cost to construct a Magic Potion with ratio " << Ma << ":" << Mb 
            << " from this set of potions is: " << result << endl;
    }

    cout << "Execution time: " << clock() << endl;
}

int solve(vector<int> a, vector<int>b, vector<int> c, int Ma, int Mb) {
    int n = a.size();

    int aTotal = 0;
    int bTotal = 0;
    int maxCost = 1;

    for (int i = 0; i < n; i++) {
        aTotal += a[i];
        bTotal += b[i];
        maxCost += c[i];
    }

    // Instead of filling the 3d array with infinity, we can fill it with a value greater
    // than the sum of all potion costs
    // It essentially functions as infinity, and adding/incrementing this value will never
    // cause the value to loop to its negative maximum (for pretty much all reasonable values)

    vector<vector<vector<int>>> MP(n+1, (vector<vector<int>> (aTotal+1, vector<int> (bTotal+1, maxCost))));

    for (int i = 0; i < n; i++) {
        MP[i][0][0] = 0;
    }

    int minCost = maxCost;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= aTotal; j++) {
            for (int k = 1; k <= bTotal; k++) {
                MP[i][j][k] = MP[i-1][j][k];
                if (((j-a[i-1]) >= 0) && ((k-b[i-1]) >= 0)) {
                    if ((MP[i-1][j-a[i-1]][k-b[i-1]] + c[i-1]) < MP[i][j][k]) {
                        MP[i][j][k] = (MP[i-1][j-a[i-1]][k-b[i-1]] + c[i-1]);
                    }
                }
                if (ratio(j, k, Ma, Mb)) {
                    minCost = min(minCost, MP[i][j][k]);
                }
            }
        }
    }

    if (minCost >= maxCost) return -1; // not possible
    else return minCost;
}

bool ratio(int a1, int b1, int a2, int b2) {
    return (a1 * b2) == (b1 * a2);
}
