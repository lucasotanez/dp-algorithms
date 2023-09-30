#include <iostream>

/* ================================== OVERVIEW ========================================

Given an integer n, find the number of distinct BSTs that can be constructed with n nodes.

Use recursive Catalan number formula.

Recursively,
DBST(n) = # of distinct BSTs that can be constructed with n nodes
DBST(n) = (sum from i=0 to n-1) DBST(i) * DBST(n-i-1)
OR: DBST(n) = (sum from i=0 to n) DBST(i-1) * DBST(n-i)

Base case:
DBST(0) = 1

Return DBST(n) as solution

Now, convert the above recursive algorithm to an iterative one using memoization.

*/

using namespace std;

int solve(int n);

int main() {
    // input parameter:
    int n = 18;

    cout << solve(n) << " BSTs can be constructed with " << n << " nodes." << endl;
    cout << "Execution: " << clock() << " ticks." << endl;
}

int solve(int n) {
    int* DBST = new int[n+1];

    // base case:
    DBST[0] = 1;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            DBST[i] += DBST[j] * DBST[i-j-1];
        }
    }

    int result = DBST[n];
    delete [] DBST;

    return result;
}
