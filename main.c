#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int memo[31][31][31]; // -1: not visited, 0: false, 1: true

// Helper function to determine if s1[i1:i1+len] is a scrambled string of s2[i2:i2+len]
int isScrambleHelper(char* s1, char* s2, int i1, int i2, int len) {
    if (memo[i1][i2][len] != -1) return memo[i1][i2][len];

    // If the substrings are identical
    if (strncmp(s1 + i1, s2 + i2, len) == 0)
        return memo[i1][i2][len] = 1;

    // Check if the substrings have the same character counts
    int count[26] = {0};
    for (int i = 0; i < len; i++) {
        count[s1[i1 + i] - 'a']++;
        count[s2[i2 + i] - 'a']--;
    }
    for (int i = 0; i < 26; i++)
        if (count[i] != 0)
            return memo[i1][i2][len] = 0;

    // Try splitting the substrings at every possible position
    for (int k = 1; k < len; k++) {
        // Case 1: No swap
        if (isScrambleHelper(s1, s2, i1, i2, k) &&
            isScrambleHelper(s1, s2, i1 + k, i2 + k, len - k)) {
            return memo[i1][i2][len] = 1;
        }
        // Case 2: Swap
        if (isScrambleHelper(s1, s2, i1, i2 + len - k, k) &&
            isScrambleHelper(s1, s2, i1 + k, i2, len - k)) {
            return memo[i1][i2][len] = 1;
        }
    }

    return memo[i1][i2][len] = 0;
}

// Main function to determine if s2 is a scrambled string of s1
int isScramble(char* s1, char* s2) {
    int len = strlen(s1);
    if (len != strlen(s2)) return 0;

    memset(memo, -1, sizeof(memo)); // Initialize memoization table
    return isScrambleHelper(s1, s2, 0, 0, len);
}

// Main function to test the isScramble function
int main() {
    // Example 1
    char s1_1[] = "great";
    char s2_1[] = "rgeat";
    printf("Input: s1 = \"%s\", s2 = \"%s\"\n", s1_1, s2_1);
    printf("Output: %s\n", isScramble(s1_1, s2_1) ? "true" : "false");

    // Example 2
    char s1_2[] = "abcde";
    char s2_2[] = "caebd";
    printf("Input: s1 = \"%s\", s2 = \"%s\"\n", s1_2, s2_2);
    printf("Output: %s\n", isScramble(s1_2, s2_2) ? "true" : "false");

    // Example 3
    char s1_3[] = "a";
    char s2_3[] = "a";
    printf("Input: s1 = \"%s\", s2 = \"%s\"\n", s1_3, s2_3);
    printf("Output: %s\n", isScramble(s1_3, s2_3) ? "true" : "false");

    return 0;
}
