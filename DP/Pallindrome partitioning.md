# Pallindrome partitioning

## Problem
Given a string of lowcase english alphabets, determine minimum number of cuts that would make each partitioned substring a pallindrome.
```
Example: "ababbbabbababa"
          3 cuts would be required “a|babbbab|b|ababa”
          
          "aaaaaaabbaaaaa"
          1 cut would be required "aa|aaaaabbaaaaa"
```
> Greedy intuition: Starting with 1st character, grow the longest pallindrome, make a cut and proceed similarily with next partition. Unfortunately, this will fail for the above given example.

## Solution
Dynamic programming :)

```
a b a b b b a b b a  b  a  b  a
0 1 2 3 4 5 6 7 9 10 11 12 13 14
```

To compute result for (0, 14). We could place a cut at all 14 spaces in-between and for each, check result for strings on left and right of cut.
Thus, the recusrion we get is
```
f(0, 14) = min(f(0,k)+f(k+1, 14))+1 where k takes 1 ,..., 13
```

We can memoise this in top-down fashion. One thing to note here is f(i,j) is 0 if substring from index i to j is already a pallindrome.

```c++
int f(string &s, int start, int end, vector<vector<int>> &dp) {
    if(start == end) {
        return dp[start][end] = 0;
    }

    if(dp[start][end] != INT_MAX)   return dp[start][end];
    
    if(isPallindrome(start, end, s)) {            // Linearly checks if substring is pallindrome
          return dp[start][end] = 0;
    }

    for(int k=start ; k<end ; k++) {
        int temp = 1 + f(s, start, k, dp, pal) + f(s, k+1, end, dp, pal);
        dp[start][end] = min(temp, dp[start][end]);
    }
    
    return dp[start][end];
}
```
Currently, we are checking everytime if substring is pallindrome linearly. Can we improve it ? Yess !!
We can maintain a 2d array where rows will indicate starting index of substring and columns, the ending index. The 2d array will be:
```
palin[i][j] = true if substring (i, j) is pallindrome
              false otherwise
```
The problem is now broken down into 2 parts: 1 calculates pallindromes and the other is concerned about calculating results.
To know if (i, j) is pallindrome, we need to check string[i] == string[j] and (i+1, j-1). Thus, we need to process smaller substrings first.
```c++
void fill_palin(string &s, vector<vector<bool>> &palin) {
     int n = s.size();
     for(int i=0 ; i<n ; i++)
        palin[i][i] = true;
     
     for(int L=2 ; L<=n ; L++) {
        for(int i=0 ; i+n-1 < n ; i++) {
            int j = i+n-1;
            palin[i][j] = (palin[i+1][j-1]) && (s[i] == s[j]);
        }
     }
}
```
Now, we can reuse the f() given above, but we can further optimize it. It is currently using recursion which will take a lot of stack space if the given input is large.
Also, 2d dp can be brought down to 1d:
```
dp[i] = minimum number of cuts for subtring (0, i)
```
Thus, we can compute the 2nd portion of solution using palin iteratively:
```c++
for (i = 0; i < n; i++) {
    if (P[0][i] == true)
        C[i] = 0;
    else {
        C[i] = INT_MAX;
        for (j = 0; j < i; j++) {
            if (P[j + 1][i] == true && 1 + C[j] < C[i])
                C[i] = 1 + C[j];
        }
    }
}
// Answer at C[n-1]
```
First, we are checking whether s[0 ... i] is palindrome or not. If its not, start checking if suffixes are palindromes. If yes, calculate result from C[k] where k < i. Keep maintaining minimum while doing this.
> Just think how above method reduced the 2 calls to f() to a single matrix lookup (1 call to f()). Hint: Think of simpler case when a string has 3 disjoint palindromes:
> str1|str2|str3  
> Earlier: (str1)|(str2str3) => (str1)|(str2)|(str3)  
> Now: (str1str2)str3 => (str1|str2)str3 => (str1|str2|str3)  
