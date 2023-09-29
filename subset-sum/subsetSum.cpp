#include <vector>
#include <iostream>

/* ================================== OVERVIEW ========================================

Given positive integers w_1, w_2, ... w_n and a target W, is it possible
to find a subset that adds exactly to the target?

Recursively,
SS(i, w) = 1 exactly when a subset (of w_i to w_n) adds to w, and 0 otherwise
SS(i, w) = SS(i+1, w) OR SS(i+1, w-w_i)
essentially, the function returns true if further numbers in the current set add to w OR
if further numbers in the set require w_i to equal exactly w

Base cases:
1. SS(i, 0) = 1
2. SS(n+1, w) = 0 (when w DNE 0) 

Return SS(1, W) as solution

Now, convert the above recursive algorithm to an iterative one using memoization.

*/

using namespace std;

bool solve(vector<int> set, int target);

void printGraph(vector<vector<bool>> g);

int main() {
    // ================ TEST CASE VARS 
    vector<int> set = {2,5,7,13,16,17,23,39};
    int target = 50;
    // ================ END TEST CASE VARS

    cout << "Set: { ";
    for (int i = 0; i < set.size(); i++) {
        cout << set[i] << " ";
    }
    cout << "}" << endl << "Target: " << target << endl;
    cout << "Solution: " << solve(set, target) << endl;

}

bool solve(vector<int> set, int target) {
    int n = set.size();

    vector<vector<bool>> SS(n+1, vector<bool>(target+1));

    // for pure c implementation, use: bool "bool SS[n+1][target+1];" instead of vector

    for (int i = 0; i <= n; i++) {
        SS[i][0] = true; // or logical 1
    }
    for (int w = 1; w <= target; w++) {
        SS[n][w] = false; // or logical 0
    }

    for (int i = n-1; i >= 0; i--) {
        for (int w = 0; w <= target; w++) {
            SS[i][w] = (SS[i+1][w] || SS[i+1][w - set[i]]);
        }
    }

    //printGraph(SS);

    return SS[0][target];
}

void printGraph(vector<vector<bool>> graph) {
    cout << endl;
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[0].size(); j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
    cout << boolalpha;
}
