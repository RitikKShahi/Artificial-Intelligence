class Solution {
public:
    using ll = long long;
    long long minMoves(vector<int>& balance) {
        int n = balance.size();
        vector<int> vecs = balance; 

        ll tsum = 0;
        int negs = -1;

        for (int i = 0; i < n; i++) {
            tsum += balance[i];
            if (balance[i] < 0) {
                negs = i;
            }
        }

        if (tsum < 0) return -1;
        if (negs == -1) return 0;

        ll lossF = -1LL * balance[negs];
        ll moves = 0;
        int calc = 1;
        
        int l = (negs - 1 + n) % n;
        int r = (negs + 1) % n;
        
        int countP = 1;

        while (lossF > 0 && countP < n) {
            if (balance[l] > 0) {
                ll take = min((ll)balance[l], lossF);
                balance[l] -= take;
                lossF -= take;
                moves += take * calc;
            }
            countP++;
            
            if (lossF == 0) break;
            
            if (countP == n) break;

            if (balance[r] > 0) {
                ll take = min((ll)balance[r], lossF);
                balance[r] -= take;
                lossF -= take;
                moves += take * calc;
            }
            countP++;
            l = (l - 1 + n) % n;
            r = (r + 1) % n;
            calc++;
        }

        return moves;
    }
};©leetcode