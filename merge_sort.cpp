#include <bits/stdc++.h>

using namespace std;

void Merge(int A[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    
    int* L = new int[n1 + 1];
    int* R = new int[n2 + 1];
    
    for (int i = 0; i < n1; i++) {
        L[i] = A[p + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = A[q + 1 + j];
    }
    
    L[n1] = numeric_limits<int>::max();
    R[n2] = numeric_limits<int>::max();
    
    int i = 0;
    int j = 0;
    
    for (int k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
    
    delete[] L;
    delete[] R;
}

void MergeSort(int A[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        Merge(A, p, q, r);
    }
}

int main() {
    int n;
    cin >> n;
    
    int* arr = new int[n];
    
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << '\n';
    
    MergeSort(arr, 0, n - 1);
    
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << '\n';
    
    delete[] arr;
}