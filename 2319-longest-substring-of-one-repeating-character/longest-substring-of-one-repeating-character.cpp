class Solution
{
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices)
    {
        int n = s.size();
        int k = queryIndices.size();
        vector<int> result(k);
        vector<char> arr(s.begin(), s.end());
        map<int, int> segments;   
        map<int, int> counts;     
        auto addLen = [&](int len)
        {
            if (len > 0)
            {
                counts[len]++;
            }
        };
        auto removeLen = [&](int len)
        {
            if (len > 0)
            {
                auto it = counts.find(len);
                it->second--;
                if (it->second == 0)
                {
                    counts.erase(it);
                }
            }
        };
        int i = 0;
        while (i < n)
        {
            int j = i;
            while (j < n && arr[j] == arr[i])
            {
                j++;
            }
            int len = j - i;
            segments[i] = len;
            addLen(len);
            i = j;
        }
        for (int q = 0; q < k; q++)
        {
            int idx = queryIndices[q];
            char c = queryCharacters[q];
            if (arr[idx] == c)
            {
                result[q] = counts.rbegin()->first;
                continue;
            }
            auto it = segments.upper_bound(idx);
            --it;
            int start = it->first;
            int len = it->second;
            int end = start + len - 1;
            segments.erase(it);
            removeLen(len);
            int leftLen = idx - start;
            int rightLen = end - idx;

            if (leftLen > 0)
            {
                segments[start] = leftLen;
                addLen(leftLen);
            }
            if (rightLen > 0)
            {
                segments[idx + 1] = rightLen;
                addLen(rightLen);
            }
            arr[idx] = c;
            int newStart = idx;
            int newLen = 1;
            if (idx > 0)
            {
                auto leftIt = segments.upper_bound(idx - 1);
                if (leftIt != segments.begin())
                {
                    --leftIt;
                    int lStart = leftIt->first;
                    int lLen = leftIt->second;
                    if (lStart + lLen - 1 == idx - 1 && arr[lStart] == c)
                    {
                        newStart = lStart;
                        newLen += lLen;
                        removeLen(lLen);
                        segments.erase(leftIt);
                    }
                }
            }
            auto rightIt = segments.find(idx + 1);
            if (rightIt != segments.end() && arr[idx + 1] == c)
            {
                newLen += rightIt->second;
                removeLen(rightIt->second);
                segments.erase(rightIt);
            }
            segments[newStart] = newLen;
            addLen(newLen);
            result[q] = counts.rbegin()->first;
        }
        return result;
    }
};