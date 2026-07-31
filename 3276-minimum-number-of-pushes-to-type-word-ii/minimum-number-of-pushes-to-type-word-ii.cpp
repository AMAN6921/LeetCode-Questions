class Solution {
public:
    int minimumPushes(string word) {
        vector<int> freq(26, 0);
        for (char c : word)
            freq[c - 'a']++;
        vector<pair<char, int>> arr;
        for (int i = 0; i < 26; i++)
            arr.push_back({i + 'a', freq[i]});
        sort(arr.begin(), arr.end(), [](const auto& a, auto& b) {
            return a.second > b.second;
        });
        int res = 0, n = arr.size();
        for (int i = 0; i < n; i++)
            res += arr[i].second * (i/8 + 1);
        return res;
    }
};