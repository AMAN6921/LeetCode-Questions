class Solution {
public:
    int minAddToMakeValid(string s) {
        int opened = 0, added = 0;
        for (char ch : s) {
            if (ch == '(') opened++;
            else if (opened) opened--;  
            else added++; 
        }
        return added + opened;
    }
};