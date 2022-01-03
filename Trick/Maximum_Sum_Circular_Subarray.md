# Maximum Sum Circular Subarray
## Problem
Given a circular integer array nums of length n, return the maximum possible sum of a non-empty subarray of nums.  
A circular array means the end of the array connects to the beginning of the array.  
  
![Capture](https://user-images.githubusercontent.com/44015508/147975986-512d0ef3-8e8b-4dcc-93ad-58f3fde86705.JPG)  

## Solution
For a normal scenario, we would have thought of Kadane's algorithm. But here 2 cases can arise:  
1. maximum sum subarray lies in middle of array
2. it spans the end and starting portion of the array

![image](https://user-images.githubusercontent.com/44015508/147976364-0bf42c59-30b8-4444-8602-496fbd82f71e.png)

Case 1 can be simply handled by Kadane.  
For the 2nd case, it can be seen that  

![image](https://user-images.githubusercontent.com/44015508/147976458-5dd2b7ff-18c2-4a64-97d4-7449c3c85008.png)

```
Thus, max subarray sum would be max(kadane for case 1, total_array_sum - min_subarray_sum)
```
1 corner case to mind:  
Suppose, we have no +ve element in the array, then max element will be a -ve element.  
In this case, (total_array_sum - min_subarray_sum) would be 0 > this (least) -ve element.
Thus, if (kadane for case 1) gives a -ve number, return that.

```c++
int maxSubarraySum(vector<int> &nums) {
    int maxsum = -100000, sum = 0;
    for(int i=0 ; i<nums.size() ; i++) {
        sum += nums[i];
        maxsum = max(sum, maxsum);
        if(sum < 0) {
            sum = 0;
        }
    }
    return maxsum;
}
int minSubarraySum(vector<int> &nums) {
    int minsum = 100000, sum = 0;
    for(int i=0 ; i<nums.size() ; i++) {
        sum += nums[i];
        minsum = min(sum, minsum);
        if(sum > 0) {
            sum = 0;
        }
    }
    return minsum;
}
int maxSubarraySumCircular(vector<int>& nums) {
    int sum = 0;
    for(auto i:nums)    sum+=i;
    int kadane = maxSubarraySum(nums), revKadane = minSubarraySum(nums);
    if(kadane < 0)
        return kadane;
    else
        return max(kadane, sum-revKadane);
}
```
Complexity: O(N) time : 2 pass algo (can be converted to single pass)  
            O(1) space
