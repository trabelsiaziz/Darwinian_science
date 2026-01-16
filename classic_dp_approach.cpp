
#include <bits/stdc++.h>


using namespace std;


#define LOCAL
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "


#define arr array
#define ll long long
#define ld long double
#define sz(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define f first 
#define s second
#define pb push_back
#define mp make_pair
#define endl '\n' 
#define NO cout << "NO" << endl
#define YES cout << "YES" << endl
#define read(v) for (auto &u : v) cin >> u;
#define print(v) for (auto u : v) cout << u << ' ';
#define int ll 



// problem data
// vector<int> values = { 5, 6, 4, 6, 5, 2};  // best score is 17
// vector<int> weights = { 6, 5, 6, 6, 3, 7}; 
vector<int> values; 
vector<int> weights; 

int KNAPSACK_CAPACITY;
int ITEM_SIZE; 


// vector<int> retrace_best_combination(){
  

// }


int solve_with_dp(){

  values.pb(-1);
  weights.pb(-1); 
  
  cin >> ITEM_SIZE; 
  cin >> KNAPSACK_CAPACITY; 

  for(int i = 0; i<ITEM_SIZE ; i++){
    int x; 
    cin >> x; 
    weights.pb(x);   
  }

  for(int i = 0; i<ITEM_SIZE ; i++){
    int x; 
    cin >> x; 
    values.pb(x); 
  }
  
  vector<vector<int>> dp(ITEM_SIZE + 1, vector<int>(KNAPSACK_CAPACITY + 1, 0)); 
  vector<int> prev(ITEM_SIZE, -1); 

   
    for(int i = 1; i <= ITEM_SIZE ; i++){
        for(int j = 1 ; j <= KNAPSACK_CAPACITY  ; j++){
            
            // take it or leave it ... it is up to you bro !!  
            dp[i][j] = dp[i-1][j]; 
            if(j - weights[i] >= 0) dp[i][j] = max(dp[i][j], dp[i-1][j - weights[i]] + values[i]);  
            
        }
    }

    return dp[ITEM_SIZE][KNAPSACK_CAPACITY]; 
}


int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);

    int res = solve_with_dp(); 
    cout << "items number : " << ITEM_SIZE << endl; 
    cout << "classic dp result : " << res << endl; 
}
