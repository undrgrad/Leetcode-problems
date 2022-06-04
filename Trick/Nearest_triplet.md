# Nearest triplet in 3 arrays
## Problem
Ninja has 3 different types of sweets. There are 'N' sweets of each type, and each sweet has a tastiness value. 
The tastiness values for sweets are given in three arrays 'A', 'B', and 'C'. 
The tastiness value of two sweets of a particular type can differ.
Ninja wants to choose 3 sweets, exactly one of each type. Let the chosen sweets' tastiness values be 'a', 'b', and 'c'. 
You need to choose the sweets such that the value of the equation abs('a' - 'b') + abs('b' - 'c') + abs('c' - 'a') is minimized. Here, abs('x') is the absolute function.

## Constraints
1 ≤ T ≤ 10
1 ≤ N ≤ 10^5
1 ≤ A[i], B[i], C[i] ≤ 10^8
It is guaranteed that the sum of 'N' is ≤ 10^5 for all test cases.

Time limit: 1 sec

## Testcases
```
2
3
7 10 7
9 10 2
3 7 8
5
10 7 1 4 6
10 1 4 5 9
9 9 10 4 8
Sample Output 1 :
4
0
----------------------
2
6
3 5 2 5 9 10
4 7 9 5 10 5
9 7 7 6 3 7
5
9 9 4 8 5
6 10 6 8 1
1 2 4 3 4
Sample Output 2 :
0
4
```

## Solution
### Naive
Brute force on all possible combinations. Time complexity: O(N^3)
### Binary Search
Iterate over all elements of first array. Let a value be 'a'. Corresponding to 'a', find upper and lower bounds in both the arrays to find closest elements to 'a'.
If 'a' is part of our solutions, we will get minimum distance in one of these 4 cases.  
Repeat this for all the arrays.  
Time complexity: O(NlogN)  
```c++
int minimumValue(int n, vector<int> a, vector<int> b, vector<int> c) {
    int ans = INT_MAX;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());
    for(int i=0 ; i<n ; i++) {
        int val = a[i];
        int bl = b[lower_bound(b.begin(), b.end(), val)-b.begin()];
        int bu = b[upper_bound(b.begin(), b.end(), val)-b.begin()];
        int cl = c[lower_bound(c.begin(), c.end(), val)-c.begin()];
        int cu = c[upper_bound(c.begin(), c.end(), val)-c.begin()];
        ans = min(ans, abs(val-bl)+abs(val-cl)+abs(bl-cl));
        ans = min(ans, abs(val-bl)+abs(val-cu)+abs(bl-cu));
        ans = min(ans, abs(val-bu)+abs(val-cl)+abs(bu-cl));
        ans = min(ans, abs(val-bu)+abs(val-cu)+abs(bu-cu));
    }
    for(int i=0 ; i<n ; i++) {
        int val = b[i];
        int bl = a[lower_bound(a.begin(), a.end(), val)-a.begin()];
        int bu = a[upper_bound(a.begin(), a.end(), val)-a.begin()];
        int cl = c[lower_bound(c.begin(), c.end(), val)-c.begin()];
        int cu = c[upper_bound(c.begin(), c.end(), val)-c.begin()];
        ans = min(ans, abs(val-bl)+abs(val-cl)+abs(bl-cl));
        ans = min(ans, abs(val-bl)+abs(val-cu)+abs(bl-cu));
        ans = min(ans, abs(val-bu)+abs(val-cl)+abs(bu-cl));
        ans = min(ans, abs(val-bu)+abs(val-cu)+abs(bu-cu));
    }
    for(int i=0 ; i<n ; i++) {
        int val = c[i];
        int bl = a[lower_bound(a.begin(), a.end(), val)-a.begin()];
        int bu = a[upper_bound(a.begin(), a.end(), val)-a.begin()];
        int cl = b[lower_bound(b.begin(), b.end(), val)-b.begin()];
        int cu = b[upper_bound(b.begin(), b.end(), val)-b.begin()];
        ans = min(ans, abs(val-bl)+abs(val-cl)+abs(bl-cl));
        ans = min(ans, abs(val-bl)+abs(val-cu)+abs(bl-cu));
        ans = min(ans, abs(val-bu)+abs(val-cl)+abs(bu-cl));
        ans = min(ans, abs(val-bu)+abs(val-cu)+abs(bu-cu));
    }
    return ans;
}
```
