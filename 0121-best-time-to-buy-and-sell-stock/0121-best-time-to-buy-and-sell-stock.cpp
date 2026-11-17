class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        int bestprice[100000];
        bestprice[0]=INT_MAX;

            for(int i=1;i<n;i++){
                bestprice[i]=min(bestprice[i-1],prices[i-1]);
            }

            int maxprofit=0;
            for(int i=0;i<n;i++){
                int currentprofit=prices[i]-bestprice[i];
                maxprofit=max(maxprofit,currentprofit);
            }
            return maxprofit;
    }
};