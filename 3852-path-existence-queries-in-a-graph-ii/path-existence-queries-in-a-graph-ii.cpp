class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        int LOG = 18;
        vector<pair<int, int>> vec;
        for (int i = 0; i < n; i++) {
            vec.push_back({nums[i], i});
        }
        sort(vec.begin(), vec.end());
        vector<int> getSortIdx(n);
        for (int i = 0; i < n; i++) {
            getSortIdx[vec[i].second] = i;
        }
        vector<vector<int>> st(n, vector<int>(LOG, 0));
        int l = 0;
        for (int r = 0; r < n; r++) {
            while (vec[r].first - vec[l].first > maxDiff) {
                st[l][0] = r - 1;
                l++;
            }
        }
        while (l < n) {
            st[l][0] = n - 1;
            l++;
        }
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                st[i][j] = st[st[i][j - 1]][j - 1];
            }
        }
        vector<int> ans(queries.size(), -1);
        for (int i = 0; i < queries.size(); i++) {
            int a = getSortIdx[queries[i][0]];
            int b = getSortIdx[queries[i][1]];
            if (a > b) swap(a, b);
            if (a == b) {
                ans[i] = 0;
                continue;
            }
            int cur = a;
            int step = 0;
            for (int j = LOG - 1; j >= 0; j--) {
                if (st[cur][j] < b) {
                    step += 1 << j;
                    cur = st[cur][j];
                }
            }
            if (st[cur][0] >= b) {
                ans[i] = step + 1;
            }
        }
        return ans;
    }
};