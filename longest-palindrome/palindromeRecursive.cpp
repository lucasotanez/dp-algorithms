#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

int LPP(int i, int j, string s);

int main() {
    string s = "YABBADABBADOO";

    cout << "The length of the longest palindromic substring of '" << s << "' is " << LPP(0, 0, s) << endl;
    cout << "Execution time: " << clock() << endl;
}

// NOTE: The parameters could simplify to just a single string with a different implementation.
// NOTE: Passing duplicate 'string s' each call 

int LPP(int i, int j, string s) {
    int current = 0;
    if ((j == s.length()) || (i == s.length())) {
        return 0;
    }
    // get string and reverse of it to check for palindrome
    string S = s.substr(i, j-i+1); string revS = S; reverse(revS.begin(), revS.end());

    if (revS == S) { current = j - i + 1; }

    int l1 = 0;
    if (i < j) l1 = LPP(i+1, j, s);
    int l2 = 0;
    l2 = LPP(i, j+1, s);
    
    if (l1 > current) current = l1;
    if (l2 > current) current = l2;

    return current;
    
}
