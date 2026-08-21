class Solution {
public:
    long long gcd(long long a, long long b) {
        while (b) {
            long long temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }
    long long lcm(long long a, long long b) {
        return a / gcd(a, b) * b;
    }
    long long count(long long x, vector<int>& coins) {
        long long ans = 0;
        int n = coins.size();
        for (int mask = 1; mask < (1 << n); mask++) {
            long long multiple = 1;
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    multiple = lcm(multiple, coins[i]);
                    cnt++;
                    if (multiple > x) break;
                }
            }
            if (multiple > x) continue;
            if (cnt % 2) ans += x / multiple;
            else ans -= x / multiple;
        }
        return ans;
    }
    long long findKthSmallest(vector<int>& coins, int k) {
        long long low = 1;
        long long high = 1LL * (*min_element(coins.begin(), coins.end())) * k;
        while (low < high) {
            long long mid = (low + high) / 2;
            if (count(mid, coins) >= k) high = mid;
            else low = mid + 1;
        }
        return low;
    }
};