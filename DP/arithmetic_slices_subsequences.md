# Arithmetic Slices - Subsequences
## Problem
Given an integer array "nums", return all the arithmetic subsequences of "nums".  
A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.  
For example,
```
[1, 3, 5, 7, 9], [7, 7, 7, 7], and [3, -1, -5, -9] are arithmetic sequences.  
[1, 1, 2, 5, 7] is not an arithmetic sequence.
```
A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.  
Example:
```
nums = [2,4,6,8,10]
ans = 7
[2,4,6]
[4,6,8]
[6,8,10]
[2,4,6,8]
[4,6,8,10]
[2,4,6,8,10]
[2,6,10]

nums = [7,7,7,7,7]
Ans = 5C3 + 5C4 + 5C5 = 16
```
  
## Solutions
### Brute Force
Enumerate all possible subsequences of "nums" and check whether they are arithmetic or not.
```c++
void dfs(int dep, vector<int> &current, int &ans, int n, vector<int> &nums) {
    if(dep == n) {
        if(current.size() < 3)  return;
        int diff = current[1] - current[0];
        for(int i=2 ; i<n ; i++) {
            if(current[i] - current[i-1] != diff)   return;
        }
        ans++;
        return;
    }
    dfs(dep+1, current, ans, n, nums);
    current.push_back(nums[dep]);
    dfs(dep+1, current, ans, n, nums);
    current.pop_back();
}

int returnAns(vector<int> nums) {
    int n = nums.size();
    int ans = 0;
    vector<int> current;
    dfs(0, current, ans, n, nums);
    return ans;
}
```

### Dynamic Programming
Let's start thinking of this problem in DP sense. Going by the first intuition, suppose that we are constructing answer where
```
DP[i] = number of all possible arithmetic subsequences in array nums[0...i]
```
Now, we will need to relate DP[i] to all DP[j] such that j<i.  
Now, what information we want if I want to build DP[i] i.e. How can we include nums[i] into the answer ?  
Forall j<i, we will try to insert nums[i] into an "appropriate" arithmetic subsequence in nums[0...j].  
And that "appropriate" arithmetic subsequence would the one which will have common difference D = nums[i] - nums[j].  
Thus, we need to know how many such arithmetic subsequences exist within nums[0...j] with the required D.  
For that, we can't just work with DP[i], we need an additional parameter: D.  
Now,
```
DP[i][d] = number of all possible arithmetic subsequences in array nums[0...i] having common difference d
```
And thus,
```
DP[0][d] = 0 forall possible d
DP[i][d] = sum(1 + DP[j][d]) where d = nums[i]-nums[j] forall j<i.
```
An example to show the working:  
![ex](https://user-images.githubusercontent.com/44015508/133022865-aafd4c9b-7f13-4199-8214-102bd8c26685.JPG)
  
Adding 1 inside sum() as [1, 2, 3] and [1, 2, 3, 4] contribute 2 to the answer.
Another problem persists.  
The range of d is [INT_MIN, INT_MAX]. Thus, creating a 2d matrix for DP  will require a lot of memory.  
Thus,  
we can use an array for storing the rows and "unordered_map" for storing the columns.

```c++
#define lli long long int
int numberOfArithmeticSlices(vector<int>& nums) {
    lli result = 0;
    lli n = nums.size();
    vector<unordered_map<lli, lli>> DP(n);
    for(int i=0 ; i<n ; i++) {
        DP.push_back(unordered_map<lli, lli>());
        for(int j=0 ; j<i ; j++) {
            lli diff = (lli)(nums[i]) - (lli)(nums[j]);
            if(diff < INT_MIN || diff > INT_MAX)    continue;
            lli d = (lli)diff;
            if(DP[i].find(d) == DP[i].end())    DP[i][d] = 0;
            if(DP[j].find(d) == DP[j].end())    DP[j][d] = 0;
            result += DP[j][d];
            DP[i][d] += 1+DP[j][d];
        }
    }
    return (int)result;
}
```
DP[j][d] denotes the total number of "generalized" arithmetic subsequence slices ending at index j with difference d. For each such slice, its length is at least 2.   
Then we are adding the element nums[i] to the end of this slice to form a new one, which means the length of the new slice will be at least 3 thus it will be a  
valid arithmetic subsequence slice. The number of these new slices will be the same as DP[j][d]. While DP[i][d] denotes the total number of "generalized" arithmetic  
subsequence slices ending at index i with difference d and it will include slices with length both greater than and equal to 2. So DP[i][d] will "over-count"  
with invalid slices of length 2.

Still, We got TLE.  
Whyyyy ???
In C++ unordered_map, when we were doing DP[j][d] = 0 when d doesn't exist in DP[j], time taken for this caused the TLE.  
A simple workaround was to access if it exists, else leave it be. Although it is nothing major visibly, but it make a difference for large test-cases.   
```c++
#define lli long long int
int numberOfArithmeticSlices(vector<int>& nums) {
    lli result = 0;
    lli n = nums.size();
    vector<unordered_map<lli, lli>> DP(n);
    for(int i=0 ; i<n ; i++) {
        DP.push_back(unordered_map<lli, lli>());
        for(int j=0 ; j<i ; j++) {
            lli diff = (lli)(nums[i]) - (lli)(nums[j]);
            if(diff < INT_MIN || diff > INT_MAX)    continue;
            lli d = (lli)diff;
            int c1 = 0, c2 = 0;
            if(DP[i].find(d) == DP[i].end());
            else    c1 = DP[i][d];
            if(DP[j].find(d) == DP[j].end());
            else    c2 = DP[j][d];
            result += c2;
            DP[i][d] = 1+c2+c1;
        }
    }
    return (int)result;
}
```

