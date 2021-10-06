# Duplicates in an array
## Problem
Find duplicates in an array of size n in which elements are between [1,n].
Examples:
```
Input: nums = [4,3,2,7,8,2,3,1]
Output: [2,3]

Input: nums = [1,1,2]
Output: [1]

Input: nums = [1]
Output: []
```  
Solution must run in O(n) and take constant space.

## Solution
### Brute force
For each element, search the whole array for duplicates.
### Memoizing
Make an auxiliary array of size n+1 which holds the count of elements seen so far.
Traverse that array at the end and enumerate the elements with count == 2.
```c++
vector<int> findDuplicates(vector<int>& nums) {
    vector<int> counts(nums.size()+1, 0);
    for(auto i: nums) {
        counts[i]++;
    }
    vector<int> ans;
    for(int i=0 ; i<=nums.size() ; i++) {
        if(counts[i]==2)
            ans.push_back(i);
    }
    return ans;
}
```
### Optimal
We will be taking advantage of the fact that the numbers are in range [1,n] and with this, we will  
avoid making an auxiliary array and memoize using the given array only.
While traversing the array, when we get the element e = nums[i], we will invert the sign of element at index  
e-1 in nums. Due to this, when we again find e in nums, we will see that element at e-1 is already -ve and so  
this e must have occurred twice.

```c++
vector<int> findDuplicates(vector<int>& nums) {
    vector<int> ans;
    for(int i=0 ; i<nums.size() ; i++) {
        int e = abs(nums[i]);
        if(nums[e-1] < 0)
            ans.push_back(e);
        else
            nums[e-1]*=-1;
    }
    return ans;
}
```
