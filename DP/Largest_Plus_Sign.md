# Largest Plus Sign

## Problem
Given an NxN matrix of 0s and 1s. Find the largest plus (+) sign that could be formed by 1s.  
Example:

![ex1](https://user-images.githubusercontent.com/44015508/132883747-56128e4c-4eae-488f-993f-88983de7beec.JPG)

![ex2](https://user-images.githubusercontent.com/44015508/132884248-d55ca7dd-7a66-4577-9a37-9d5afb18cd13.JPG)

Thus, answer would be 5.

## Solution
### Brute Force

In this, we can simply go to each cell and try to expand the plus sign in all directions.  
```c++
int maxPlusSize(vector<vector<int>> Matrix) {
    int N = Matrix.size();
    int ans = 0;
    for(int r=0 ; r<N ; r++) {
        for(int c=0 ; c<N ; c++) {
            int k=0;
            while(k <= r && r < N-k && k <= c && c < N-k && Matrix[r-k][c] && Matrix[r+k][c] && Matrix[r][c-k] && Matrix[r][c+k])
                k++;
            ans = max(ans, k);
        }
    }
    return ans;
}
```

### Dynamic Programming :-)

Can we somehow optimize the innermost loop ? If at each cell, we know the number of continous 1s in all 4 directions,  
then we can simply take minimum of the 4 values. 
Now, we can precompute the 4 values separately for all the cells.
```
If Matrix[r][c] = 0, then dp[r][c] = 0.
Else, dp[r][c] = 1+count (maintained in 1 particular direction)

For left direction (right to left), if the row is 01110110, then corresponding values are 01230120.
```
Thus, dp[r][c] can store the minimum of all 4 values.

```c++
int maxPlusSize(vector<vector<int>> Matrix) {
    int N = Matrix.size();
    vector<vector<int>> dp(N, vector<int>(N, 0));
    for(int r=0 ; r<N ; r++) {
        int count = 0;
        for(int c=0 ; c<N ; c++) {
            if(Matrix[r][c] == 0)
                count = 0;
            else
                count++;
            dp[r][c] = count;
        }
        count = 0;
        for(int c=N-1 ; c>=0 ; c--) {
            if(Matrix[r][c] == 0)
                count = 0;
            else
                count++;
            dp[r][c] = min(dp[r][c], count);
        }
    }
    int ans = 0;
    for(int c=0 ; c<N ; c++) {
        int count = 0;
        for(int r=0 ; r<N ; r++) {
            if(Matrix[r][c] == 0)
                count = 0;
            else
                count++;
            dp[r][c] = min(dp[r][c], count);
        }
        count = 0;
        for(int r=N-1 ; r>=0 ; r--) {
            if(Matrix[r][c] == 0)
                count = 0;
            else
                count++;
            dp[r][c] = min(dp[r][c], count);
            ans = max(ans, dp[r][c]);
        }
    }
    return ans;
}
```

