# Maximum Length Subarray with Positive Product
## Problem
Given an array of integers nums, find the maximum length of a subarray where the product of all its elements is positive.  
Return the maximum length of a subarray with positive product.
```
Input: nums = [1,-2,-3,4]
Output: 4

Input: nums = [0,1,-2,-3,-4]
Output: 3

Input: nums = [-1,-2,-3,0,1]
Output: 2
```
## Solution
### Greedy
This problem was done in conjuction with maximum product subarray problem. Thus, the greedy solution is inspired from its greedy solution.

### DP
This is again motivated from maximum product subarray problem. Here, again, 2 problems will be solved simultaneoulsy (as both are supplementary to each other):
1. max length subarray with +ve product and 2. max length subarray with -ve product.

As again, we have to compute the subarray, we will consider inclusion of ith element while processing it. Motivating from mentioned question,
```
Let pos[i] = max length of subarray with +ve product with including nums[i]
and neg[i] = max length of subarray with -ve product with including nums[i]

Let curr = nums[i]
if curr = 0, pos[i] and neg[i] will be 0
if curr > 0, pos[i] = pos[i-1] + 1 (adding +ve int to max length subarray with +ve product)
             neg[i] = (neg[i-1] > 0) ? neg[i-1] + 1 : 0 (adding +ve int to max length subarray with -ve product)
if curr < 0, pos[i] = (neg[i-1] > 0) ? neg[i-1] + 1 : 0 (if subarray is there with -ve product, adding -ve int to subarray makes product +ve, else no +ve product subarray with -ve int only)
             neg[i] = pos[i-1] + 1
```
Complexity: Time : O(N) and Space : O(N) - can be optimized to 2 variables though so O(1)
```c++
int getMaxLen(vector<int>& nums) {
    int n = nums.size();
    int pos[n+1], neg[n+1];
    memset(pos, 0, (n+1)*sizeof(int));
    memset(neg, 0, (n+1)*sizeof(int));
    for(int i=1 ; i<=n ; i++) {
        int val = nums[i-1];
        if(val == 0) {
            pos[i] = neg[i] = 0;
        }
        else if(val > 0) {
            pos[i] = pos[i-1] + 1;
            if(neg[i-1] > 0)
                neg[i] = neg[i-1] + 1;
        }
        else {
            if(neg[i-1] > 0)
                pos[i] = neg[i-1]+1;
            neg[i] = pos[i-1]+1;
        }
    }
    int ans = INT_MIN;
    for(int i=1 ; i<=n ; i++)    ans = max(ans, pos[i]);
    return ans;
}
```
