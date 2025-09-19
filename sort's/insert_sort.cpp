#include <bits/stdc++.h>
using namespace std;

void insert_sort(int a[], int n) {
    for (int j = 1; j < n; j++) {
        int x = a[j];
        int i = j - 1;
        while (i >= 0 && a[i] > x) {
            a[i + 1] = a[i];
            i--;
        }
        a[i + 1] = x;
    }
}
int main() {
    int n; 
    cin >> n;
    int a[n];  
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    insert_sort(a, n);  
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << '\n';
    return 0;
}