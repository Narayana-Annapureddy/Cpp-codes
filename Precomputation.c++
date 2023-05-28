#include<iostream>
#include<vector>
using namespace std;
// Pre computation means we compute answers before the problem and get the answers in O(1)
// use 1 based indexing in this problems

int gcd(int a, int b) {
    if (b==0)
        return a;
    return gcd(b, a%b);
}

// Given an array with left and right index need to compute the gcd for left side of left and right of right
void gcdQueries() {

    vector<int> v = {0};  // consider index from 1 so start loop from 1  (0 is in index 0 i.e dummy)
    int n, t, x;
    cin >> n;
    for(int i=1; i<=n; i++) {
        cin >> x;
        v[i] = x;
    }
    cin >> t;    // read size of array next array elements then no.of testcases

    vector<int> forward(n+1);   // computes gcd from first element to ith element
    vector<int> backward(n+1);  // computes gcd from ith element to last element
    forward[0] = backward[n+1] = 0;     // pre computation of results
    for(int i=1; i<=n; i++) {   
        forward[i] = gcd(forward[i-1], v[i]);
    }
    for(int i=n; i>=0; i--) {
        backward[i] = gcd(backward[i+1], v[i]);
    }

    // Now start solving the queries by directly taking pre computation results from forward and backward
    while (t--)  {
        int l, r;
        cin >> l >> r;  // remove elements in range [l,r] (inclusive)
        // so compute forward[l-1] and backward[r+1] and find gcd for both of them
        int result = gcd(forward[l-1], backward[r+1]);
        cout << result << endl;
    }
    
}

const int N = 1e7+10;
long long int arr[N];  // use precomputation technique

void UpdateLtoRQuery() {
    int n, m;
    cin >> n >> m;
    while(m--) {        // need to use prefix sum like notation
        int a, b, d;
        cin >> a >> b >> d;        // add d at index a and subtract d at index b+1
        arr[a] += d;              // ex:    2   4   5     (add 5 from index 2 to 4)
        arr[b+1]  -= d;           //     0 5 0 0 -5     (at index 2 5 is added and at index 5 -5 is done)
    }                             //     0 5 5 5  0     (if we do prefix sum)        
    for(int i=1; i<=n; i++) {
        arr[i] += arr[i-1];       // now after doing prefix sum we get original array
    }                     
    long long mx = arr[0];
    for(int i=1; i<=n; i++) {
        if (mx < arr[i])
            mx = arr[i];
    }
    cout << mx << endl;
}

int main() {
    UpdateLtoRQuery();
}
