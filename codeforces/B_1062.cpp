// @Dubega(Sousxs)
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
    
void solve(int q){
    int n; cin >> n;
    vector<char> s(n);
    vector<char> t(n);
    for(int i=0;i<n;i++) cin >> s[i];
    for(int i=0;i<n;i++) cin >> t[i];
    
    sort(s.begin(),s.end());
    sort(t.begin(),t.end());
    
    if(s==t)
        cout << "YES\n";
    else
        cout << "NO\n";
}
    
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q; cin >> q;
    while(q--) solve(q);
    return 0;
}