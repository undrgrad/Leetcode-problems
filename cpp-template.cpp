#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define ull unsigned long long
#define lli long long int

ull nCk(int n, int k) {
  ull N = n, K = k;
  ull ans = 1;
  if(k > n-k)
    k = n-k;
  for(i=0 ; i<k ; i++) {
    res *= (n - i);
    res /= (i+1);
  }
  return res;
}




// String building: stringstream s; s << "<string>"; s.str();

vector<string> tokenize_string(string s) { // efficient way to return vectors
	stringstream ss(s);
	vector<string> tokens;
	string temp;
	while(ss, temp, ' ') {
		tokens.pb(temp);
	}
	return tokens;
}

void solve() {

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int testcases = 1;
	cin >> testcases;
	for(int i=0 ; i<testcases ; i++)	solve();

	return 0;
}
