#include <stdio.h>

int findJudge(int n, int trustSize, int** trust) {
    // Arrays to keep track of trust relationships
    int trust_count[n + 1];  // to count how many people trust each person
    int is_trusted[n + 1];    // to keep track of how many people each person trusts

    // Initialize arrays with zeros
    for (int i = 0; i <= n; i++) {
        trust_count[i] = 0;
        is_trusted[i] = 0;
    }

    // Update the trust counts based on the trust relationships
    for (int i = 0; i < trustSize; i++) {
        int a = trust[i][0];
        int b = trust[i][1];
        trust_count[b]++;
        is_trusted[a]++;
    }

    // Check for the person who trusts no one and is trusted by everyone else (except themselves)
    for (int i = 1; i <= n; i++) {
        if (trust_count[i] == n - 1 && is_trusted[i] == 0) {
            return i;  // Return the label of the town judge
        }
    }

    return -1;  // If no town judge is found
}

int main() {
    int n = 4;
    int trustSize = 5;
    int trust[5][2] = {{1,3},{1,4},{2,3},{2,4},{4,3}};
    printf("%d\n", findJudge(n, trustSize, trust));  // Output: 3
    return 0;
}
