# Knapsack_(vanilla+large_weights)
## Problem Statement
There are N items, numbered 1,2,…,N. For each i (1≤i≤N), Item i has a weight of wi and a value vi.  
Taro has decided to choose some of the N items and carry them home in a knapsack. The capacity of the knapsack is W, which means that the sum of the weights of items taken must be at most W.
Find the maximum possible sum of the values of items that Taro takes home.

Examples:
```
N=3 W=8
Weights: 3 4 5
Values: 30 40 50

N=5 W=5
Weights: 1 1 1 1 1
Values: 1000000000 1000000000 1000000000 1000000000 1000000000

N=6 W=15
Weights: 6 5 6 6 3 7
Values: 5 6 4 6 5 2
```
### Constraints
1≤N≤100  
1≤W≤10^5  
1≤wi≤W  
1≤vi≤10^9  

Now, the first approach that comes to mind is to solve this recursively. Let's try to see what do we need to get solution for index i and knapsack weight w ?  
Let it be maxVal(i, w). Looking at every i, we have two choices, whether Taro chooses item i or he doesn't.  
That means, if he chooses, max(i-1,W-wi) will needs to be solved recursively given that W >= wi. If he doesn't, max(i-1,W) will be solved recursively.  
As we have to maximize the value, we will take max of both.  
Thus, 
```
If W >= wi,
maxVal(i,W) = max(maxVal(i-1,W), maxVal(i-1,W-wi) + vi)
Else
maxVal(i,W) = maxVal(i-1,W) 
```

Recusrive solution:
```c++
#include<bits/stdc++.h>
using namespace std;
 
#define ull long long
 
ull max_sum(ull ind, ull w, ull* wt, ull* val) {
	if(ind < 0)
		return 0;
	if(w == 0)
		return 0;
	ull with = FLT_MIN;
	if(w >= wt[ind])
		with = val[ind] + max_sum(ind-1, w - wt[ind], wt, val);
	ull without = max_sum(ind-1, w, wt, val);
	ull ans = max(with, without);
	return ans;
}
 
int main() {
	ull n, w;
	cin >> n;
	cin >> w;
	ull wt[n], val[n];
	for(ull i=0 ; i<n ; i++) {
		cin >> wt[i];
		cin >> val[i];
	}
	printf("%lld\n", max_sum(n-1, w, wt, val));
 
}
```

To convert it into a DP solution, we can build a 2D table bottom-up like this:
```
If j >= wi
dp[i][j] = max(dp[i-1][j], dp[i-1][j-wi] + vi)
Else
dp[i][j] = dp[i-1][j]
```
Thus,
```c++
#include<bits/stdc++.h>
using namespace std;
 
#define ull unsigned long long
 
int main() {
	int N, W;
	cin >> N >> W;
	int weight[N], val[N];
	for(int i=0 ; i<N ; i++) {
		cin >> weight[i] >> val[i];
	}
	ull dp[N+1][W+1];
	memset(dp, 0, sizeof(dp));
	for(int i=1 ; i<=N ; i++) {
		for(int j=1 ; j<=W ; j++) {
			dp[i][j] = dp[i-1][j];
			if(j >= weight[i-1])
				dp[i][j] = max(dp[i][j], dp[i-1][j-weight[i-1]]+val[i-1]);
		}
	}
	printf("%lld\n", dp[N][W]);
}
```
### Constraints
1≤N≤100  
1≤W≤10^9  
1≤wi≤W 
1≤vi≤10^3  

Now, we can't use the above approach as for that our DP table if of NxW which won't be possible as W is of order 10^9. But at the same time, we see
that vi's are of the order 10^3. Can we somehow turn our DP states in terms of vi's ?  
Here,  we can look at the inverse problem: find the minimum weight of knapsack needed to carry things of value V.  
Say, we have explored until index i and we want to find minimum weight of knapsack needed to carry things of value V, what should we consider ?  
First, if V >= vi, current item can contribute and its weight will be included in the answer. Else, we can also ignore it.  
Also, we have to want weights which represent correct sum of values: for this, we penalize using dp[0][x] = very large value.
Recurrence becomes:
```
If j >= vi
dp[i][j] = min(dp[i-1][j], dp[i-1][j-vi] + wi)
Else
dp[i][j] = dp[i-1][j]
dp[i][0] = 0 forall i
dp[0][i] = inf forall i
```
So,
```c++#include<bits/stdc++.h>
using namespace std;

#define ull unsigned long long

int main() {
	int N, W, val_sum=0;
	cin >> N >> W;
	int weight[N+1], val[N+1];
	for(int i=1 ; i<=N ; i++) {
		cin >> weight[i];
		cin >> val[i];
		val_sum += val[i];
	}

	ull dp[N+1][val_sum+1];
	for(int i=0 ; i<=N ; i++)	dp[i][0] = 0;
	for(int i=1 ; i<=val_sum ; i++)	dp[0][i] = 1e9+7;
	for(int i=1 ; i<=N ; i++) {
		for(int j=1 ; j<=val_sum ; j++) {
			if(j-val[i]>= 0)
				dp[i][j] = min(dp[i-1][j], dp[i-1][j-val[i]]+weight[i]);
			else
				dp[i][j] = dp[i-1][j];
		}
	}
	int ans = 0;
	for(int i=1 ; i<=val_sum ; i++) {
		if(dp[N][i] <= W)
			ans = max(ans, i);
	}
	printf("%d\n", ans);
}
```
