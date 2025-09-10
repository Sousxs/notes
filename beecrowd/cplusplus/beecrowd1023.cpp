#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define int long long
#define MAX 1000005

void solve(int n){
    map<int, int> mp;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        mp[x]=y/x;
    }
    for(auto p: mp)
        cout << p.first << "-" << p.second << " ";
}
int32_t main(){
    int n;
    while(cin >> n && n){
        solve(n);
    }
}
