#include <bits/stdc++.h>
using namespace std;
int lengthOfLongestSubstring(string s){
    map<char,int> result;
    for(char c : s){
        result[c]++;
    }
    return result.size();
}
int main(){
    string s = "pwwkew";
    cout << lengthOfLongestSubstring(s) << endl;
    return 0;
}