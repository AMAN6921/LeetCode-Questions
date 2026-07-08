class Solution {
#define ll long long int
const ll mod = 1e9 + 7;
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        ios_base::sync_with_stdio(false);
        cin.tie(0);
        int n = s.size();
        vector<int> res, ind, d;
        for (int i = 0; i < n; i++) {
            if (s[i] != '0') {
                ind.push_back(i);
                d.push_back(s[i] - '0');
            }
        }
        int sz = ind.size();
        vector<ll> m(sz + 1, 1), pre(sz + 1), ps(sz + 1);
        for (int i = 1; i <= sz; i++) {
            m[i] = (m[i - 1] * 10) % mod;
            pre[i] = (pre[i - 1] * 10 + d[i - 1]) % mod;
            ps[i] = ps[i - 1] + d[i - 1];
        }
        for (const auto &q : queries) {
            int l = q[0], r = q[1];
            int lo = lower_bound(ind.begin(), ind.end(), l) - ind.begin();
            int hi = upper_bound(ind.begin(), ind.end(), r) - ind.begin() - 1;
            if (lo > hi) {
                res.push_back(0);
                continue;
            }
            ll c = hi - lo + 1;
            ll x = (pre[hi + 1] - (pre[lo] * m[c]) % mod + mod) % mod;
            ll sum = ps[hi + 1] - ps[lo];

            res.push_back((x * sum) % mod);
        }
        return res;
    }
};