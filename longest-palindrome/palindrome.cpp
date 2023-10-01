#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

/* ================================== OVERVIEW ========================================

Given a string S, find the longest possible palindromic substring.

Recursively,
LPP(i, j) = longest palindromic substring between indexes i and j of the string
LPP(i, j) = max(current, LPP(i+1, j) (ONLY IF i < j), LPP(i, j+1))
The largest length will propogate up the call stack

Base cases: When i or j equals n (out of bounds)
1. LPP(x, n) = 0
2. LPP(n, x) = 0

Return LPP(0, 0) as solution

Now, convert the above recursive algorithm to an iterative one using memoization.

*/

using namespace std;

int solve(string s);

bool isPalindrome(string s);

int main() {
    string s = "YABBADABBADOO";

    cout << "The length of the largest palindromic substring of '" << s << "' is " << solve(s) << endl;
    cout << "Execution time: " << clock() << endl;
}

int solve(string s) {
    int i, j;
    i = j = 0;

    int n = s.size();

    vector<vector<int>> LPP(n+1, vector<int>(n+1, 0));
    // base case covered in the graph initialization above

    for (int i = n-1; i >= 0; i--) {
        for (int j = n-i-1; j >= 0; j--) {
            /*
                NOTE:
                When calculating the substring and the length of the substring, offset 
                the last index by +1.

                i and j are indexes here, so a substring from index i to index j would
                be of length j - i + 1.

                Example: i=0 and j=1
                    Substring starting at index 0 that CONTAINS 1 (j) elements is only
                    length 1. But, we want the substring that starts at 0 and ENDS at 1,
                    which is length 2. (see ".substr(start, length)") on cppreference.com.
                    The real length of this substring is 2. Offsetting must be done in
                    the .substr() function call AND in assigning j - i + 1 to "LPP[i][j]".

                This probably would not be an issue when using a language like Python.
            */
            if (isPalindrome(s.substr(i, j-i+1))) LPP[i][j] = j - i + 1;
            else LPP[i][j] = 1;
            // now, get "max" length
            if (LPP[i][j+1] > LPP[i][j]) LPP[i][j] = LPP[i][j+1];
            if (LPP[i+1][j] > LPP[i][j]) LPP[i][j] = LPP[i+1][j];
        }
    }

    // Uncomment to see iterative graph
    //cout << endl;
    //for (int i = 0; i <= n; i++) {
    //    for (int j = 0; j <= n-i-1; j++) {
    //        cout << LPP[i][j] << " ";
    //    }
    //    cout << endl;
    //}

    return LPP[0][0];
}

bool isPalindrome(string s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    return (rev == s);
}
