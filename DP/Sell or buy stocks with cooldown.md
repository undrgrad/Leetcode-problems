# Best time to buy and sell stocks with cooldown
## Problem
You are given an array prices where prices[i] is the price of a given stock on the ith day.  
Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy 
one and sell one share of the stock multiple times) with the following restrictions:  
After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).  
Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).  

Example: 
```
Input: prices = [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]
```

## Solution - DP :-)
Here, cooldown period is the nuisance.  
Now, at each day, we have to make a decision: buy stock, sell stock or cooldown.
So, let buy[i] = maxProfit when 0 to i days ends with the ith day being a buy stock day
        sell[i] = maxProfit when 0 to i days ends with the ith day being a sell stock day  

Every buy is preceded with atlease a cooldown day and every sell is succeeded by atleast a cooldown day.  

We can see that:
```
buy[i] = max(sell[i-2] - prices[i], buy[i-1]) // 1st - actually buying stock and spending money 2nd - cooling downtoday
sell[i] = max(buy[i-1] + prices[i], sell[i-1]) // 1st - selling stock today 2nd - cooling down today
```
At day 1, we will have nothing to sell so profit = 0 => sell[i] = 0.  
Also, we will buy the stock on day 1. So, buy[i] = - prices[i] as current maxprofit is 0.  
So,
```c++
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<int> buy(n, 0), sell(n, 0);
    buy[0] = -prices[0];
    for(int i=1 ; i<n ; i++) {
        if(i>=2)
            buy[i] = max(buy[i-1], sell[i-2] - prices[i]);
        else
            buy[i] = max(buy[i-1], -prices[i]);             // - prices[i] to buy the stock on 2nd day as well
        sell[i] = max(sell[i-1], buy[i-1] + prices[i]);
    }
    int ans = 0;
    for(int i=0 ; i<n ; i++)    ans = max(ans, sell[i]);
    return ans;
}
```
Time: O(N) space: O(N) can be converted to O(1)  
