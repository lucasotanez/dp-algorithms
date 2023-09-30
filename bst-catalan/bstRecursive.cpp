#include <iostream>

using namespace std;

int DBST(int n);

int main() {
    // input parameter:
    int n = 18;

    cout << DBST(n) << " BSTs can be constructed with " << n << " nodes." << endl;
    cout << "Execution: " << clock() << " ticks." << endl;
}

int DBST(int n) {
    if (n == 0) return 1;

    int total = 0;

    for (int i = 0; i < n; i++) {
        total += DBST(i) * DBST(n-i-1);
    }

    return total;
}
