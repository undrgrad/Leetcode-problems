# Missing Coin Sum
## Problem
You have n coins with positive integer values. What is the smallest sum you cannot create using a subset of the coins?

## Constraints
1 ≤ n ≤ 2x10^5  
1 ≤ xi ≤ 10^9

## Test cases
```
5
2 9 1 2 7
Ans = 6

4
1 1 3 4
Ans = 10

6
1 2 3 4 5 6
Ans = 22
```

## Solution
### Brute Force
Generate all possible subsets, compute their sum and then search for first +ve such integer.

### Dynamic Programming
Let's first sort the array. Next, assume that we have an answer "res" for arr[0 ... i-1].  
That means, subset sums of arr[0 ... i-1] can generate all intergers from 1 to "res"-1.  
Now 2 cases:  
1. if "res" < arr[i], then we have found a gap (as array is sorted) and "res" is our answer.
2. if "res" >= arr[i], then arr[0 ... i-1] can generate all integers from 1 to "res"+arr[i]-1 in which case "res"+arr[i] will be our answer upto arr[0 ... i].

```c++
#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long

int main() {
    int n; cin >> n;
    int arr[n];
    for(int i=0 ; i<n ; i++)    cin >> arr[i];
    ull res = 1;
    sort(arr, arr+n);
    for(int i=0 ; i<n ; i++) {
        if(res < arr[i]) {
            break;
        }
        else
            res += arr[i];
    }
    printf("%llu\n", res);
}
```
