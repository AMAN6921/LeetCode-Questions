class Solution {
public:
    int MOD = 1e9 + 7;
    pair<int, int> dfs(int r, int c, vector<string>& board,
    vector<vector<pair<int, int>>>& dp) {
        int n = board.size();
        if (r < 0 || c < 0 || board[r][c] == 'X')
            return {-1, 0};
        if (r == 0 && c == 0)
            return {0, 1};
        if (dp[r][c].first != -2)
            return dp[r][c];
        auto left = dfs(r, c - 1, board, dp);
        auto up = dfs(r - 1, c, board, dp);
        auto diag = dfs(r - 1, c - 1, board, dp);
        int maxScore = max({left.first, up.first, diag.first});
        int ways = 0;
        if (maxScore == -1)
            return dp[r][c] = {-1, 0};
        if (left.first == maxScore)
            ways = (ways + left.second) % MOD;
        if (up.first == maxScore)
            ways = (ways + up.second) % MOD;
        if (diag.first == maxScore)
            ways = (ways + diag.second) % MOD;
        if (isdigit(board[r][c]))
            maxScore += board[r][c] - '0';
        return dp[r][c] = {maxScore, ways};
    }
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        vector<vector<pair<int, int>>> dp(n,
        vector<pair<int, int>>(n, {-2, -2}));
        auto res = dfs(n - 1, n - 1, board, dp);
        if (res.second == 0)
            return {0, 0};
        return {res.first, res.second};
    }
};