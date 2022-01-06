# Maximum Product Subarray
## Problem
Given an integer array nums, find a contiguous non-empty subarray within the array that has the largest product, and return the product.  
```
Input: nums = [2,3,-2,4]
Output: 6

Input: nums = [-2,0,-1]
Output: 0
```
## Solution
### Greedy
One way to think about it is: 0 should never be included in the maximal subarray. Thus, our solution will be found in one of the subarrays obtained
after partitioning the given array around 0.  
Thus, we have to find maximal such subarray in each partition p.  
Now consider each such partition p = (a1, a2, ... , aN):
If there are even number of -ve integers in p, then our contender answer (for this partitino) will simply be product of all the a's.
But is there are odd number of -ve integers, (say 5), then (let a1 ... a5 be those -ve ints)
```
[..., a1, ..., a2, ..., a3, ..., a4, ..., a5, ...]
to get max product, we either need to consider product of [..., a1, ..., a2, ..., a3, ..., a4, ...] or [..., a2, ..., a3, ..., a4, ..., a5, ...] 
(to get even -ve ints in product which when multiplied will give +ve) whichever is greater.
Thus, this can again be computed in O(N)
```
For each such segment p, we will simply take max of all the contenders.  
If this max is -ve and 0 is in given array, then ans is 0 else max.

```c++
#define lli long long int
int retMax(vector<int> &nums, int s, int e) {
    if(s==e && nums[s]<0)
        return nums[s];
    lli prod = 1;
    for(int i=s ; i<=e ; i++) {
        prod *= nums[i];
    }
    if(prod > 0)
        return (int)prod;
    lli div1 = 1;
    int i=s;
    for(; i<=e && nums[i] > 0; i++) {
        div1 *= nums[i];
    }
    if(i<=e && nums[i] < 0) {
        div1 *= nums[i];
    }
    lli div2 = 1;
    i=e;
    for(; i>=s && nums[i] > 0; i--) {
        div2 *= nums[i];
    }
    if(i>=s && nums[i] < 0) {
        div2 *= nums[i];
    }
    return max(prod/div1, prod/div2);
}

int maxProduct(vector<int>& nums) {
    int maxAns = INT_MIN;
    int i=0, j=0, n = nums.size();
    bool zero = false;
    if(n==1)
        return nums[0];
    for(i=0 ; i<n && j<n; i++) {
        if(nums[i] == 0) {
            zero = true;
            continue;
        }
        j=i;
        for(;j+1<n && nums[j+1]!=0; j++);
        int its_max = retMax(nums, i, j);
        i = j;
        maxAns = max(maxAns, its_max);
    }
    if(maxAns < 0 && zero) {
        return 0;
    }
    return maxAns;
}
```

## DP
Let's analyze special property about maximum product subarray. If we have a very large -ve number at some index and we know that it will be a part of
the solution, then when will we incorporate that ? For this, we need to maintain something for most -ve value seen for subarray. Thus, we will be solving 2
problems simultaneously (both will be using each other): maximum product subarray and minimum product subarray.  
For this, we will be building a subarray ==> continuity. Thus, we think of our sub problem keeping in mind that current element will be included in solution.
So,
```
Let Max[i] = maximum product subarray value when including arr[i] in solution.
and Min[i] = minimum product subarray value when including arr[i] in solution.

Max[i] will be max of (current element, Min[i-1]*current ele (case when current ele is large -ve), Max[i-1]*current ele (case when current ele is large +ve))
Min[i] will be min of (current element, Min[i-1]*current ele (case when current ele is large +ve), Max[i-1]*current ele (case when current ele is large -ve))
```
As we are only concerned with (i-1)th values of Max and Min, we can use 2 variables rather than arrays.  
So, complexity - Time: O(N) and Space: O(1)

```c++
int maxProduct(vector<int>& nums) {
    int n = nums.size();
    int Min[n], Max[n];
    memset(Min, 0, n*sizeof(int));
    memset(Max, 0, n*sizeof(int));
    Min[0] = Max[0] = nums[0];
    for(int i=1 ; i<n ; i++) {
        Min[i] = min(nums[i], min(nums[i]*Min[i-1], nums[i]*Max[i-1]));
        Max[i] = max(nums[i], max(nums[i]*Min[i-1], nums[i]*Max[i-1]));
    }
    int ans = INT_MIN;
    for(int i=0 ; i<n ; i++)    ans = max(ans, Max[i]);
    return ans;
}
```
