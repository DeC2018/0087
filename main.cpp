#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class Solution {
public:
    bool isScramble(string s1, string s2) {
        int n = s1.size();
        vector<vector<vector<int>>> f(n, vector<vector<int>>(n, vector<int>(n + 1, -1))); // 3D DP array

        // Recursive function with memoization
        function<bool(int, int, int)> dfs = [&](int i, int j, int k) -> bool {
            if (f[i][j][k] != -1) { // If already computed, return the result
                return f[i][j][k] == 1;
            }
            if (k == 1) { // Base case: single character comparison
                return f[i][j][k] = (s1[i] == s2[j]);
            }
            for (int h = 1; h < k; ++h) {
                // Check if the substrings are scrambled without swapping
                if (dfs(i, j, h) && dfs(i + h, j + h, k - h)) {
                    return f[i][j][k] = true;
                }
                // Check if the substrings are scrambled with swapping
                if (dfs(i + h, j, k - h) && dfs(i, j + k - h, h)) {
                    return f[i][j][k] = true;
                }
            }
            return f[i][j][k] = false; // If no valid scramble is found
        };

        return dfs(0, 0, n); // Start the recursion from the full strings
    }
};

int main() {
    Solution solution;

    // Example 1
    string s1_1 = "great";
    string s2_1 = "rgeat";
    cout << "Input: s1 = \"" << s1_1 << "\", s2 = \"" << s2_1 << "\"" << endl;
    cout << "Output: " << (solution.isScramble(s1_1, s2_1) ? "true" : "false") << endl;

    // Example 2
    string s1_2 = "abcde";
    string s2_2 = "caebd";
    cout << "Input: s1 = \"" << s1_2 << "\", s2 = \"" << s2_2 << "\"" << endl;
    cout << "Output: " << (solution.isScramble(s1_2, s2_2) ? "true" : "false") << endl;

    // Example 3
    string s1_3 = "a";
    string s2_3 = "a";
    cout << "Input: s1 = \"" << s1_3 << "\", s2 = \"" << s2_3 << "\"" << endl;
    cout << "Output: " << (solution.isScramble(s1_3, s2_3) ? "true" : "false") << endl;

    return 0;
}
