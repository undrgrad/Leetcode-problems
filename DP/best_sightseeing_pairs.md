# Best Sight-seeing Pairs
## Problem
You are given an integer array values where values[i] represents the value of the ith sightseeing spot. 
Two sightseeing spots i and j have a distance j - i between them.  
The score of a pair (i < j) of sightseeing spots is values[i] + values[j] + i - j: the sum of the values of the sightseeing spots,
minus the distance between them.
Return the maximum score of a pair of sightseeing spots.  

Example:
```
Input: values = [8,1,5,2,6]
Output: 11
Explanation: i = 0, j = 2, values[i] + values[j] + i - j = 8 + 5 + 0 - 2 = 11

Input: values = [1,2]
Output: 2
```

## Solution
### Brute Force
Simple brute force will be to simply check if two spots give the maximum score.  
This will be an O(N^2) approach.

### DP :-)
Let's look at the optimal answer: it will be two indexes i and j for which score will be max and i < j.  
Visualise the formula as values[i] + values[j] - (j-i) => score decreases as separation increases.  
If we can know, what is the highest valued spot until j for each such j, then we can simply take max of all these scores.  
Let's fix a j. Value of a spot i < j will be value[i] + (distance from j = i-j).  
We need to compute highest valued spot in values[0 ... j-1]. If we know the answer for values[0 ... j-2] (say x), then
```
highest valued spot in values[0 ... j-1] = max(values[j-1], x-1)
```
-1 as we are carrying an older but greater value so its distance will increase from j and so, score will decrease.  

```c++
int maxScoreSightseeingPair(vector<int>& values) {
    int n = values.size();
    vector<int> dp(n, 0);
    dp[0] = values[0];
    for(int i=1 ; i<n ; i++) {
        dp[i] = max(dp[i-1] - 1, values[i]);
    }
    int ans = 0;
    for(int i=1 ; i<n ; i++) {
        int score = values[i] + dp[i-1] - 1;
        ans = max(ans, score);
    }
    return ans;
}
```
Complexity: Time = O(N) and space = O(N). Code can easily modfied to work in just 1 loop and a variable can be used for dp.  
