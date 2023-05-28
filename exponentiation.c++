#include<iostream>
using namespace std;

// moudlar properties
// (a+b)%m =  ( a%m + b%m ) % m
// (a-b)%m =  ( a%m - b%m ) % m
// (a*b)%m =  ( a%m * b%m ) % m
// (a/b)%m =  ( a%m * (b^-1)%m ) % m

void power() {
    int a=3, n=13;         // 13  =  bin(1101)  (8 + 4 + 0 + 1)  (3^13 = 3^8 x 3^4 x 3^0 x 3^1)
    int res = 1;           // so 0th bit has weight 3^1, 1st has no weight, 2nd has 3^4, 3rd has 3^8
    while(n) {             // so when we get 1(odd) we multiply it to res of existing a value
        if (n&1)           // and 0 has no contribution in result
            res = res*a;
        a = a*a;          // every time we should get doubled (3^1, 3^2, 3^4, 3^8, 3^16, 3^32.....)
        n >>= 1;          // just pop every bit from right side as loop repeat for no.of binary bits of number n 
    }
    cout << res << endl;
}

// find (a^n)%m
void binModExpon() {
    int a=4, n=3, m = 1e9+7;
    int res = 1; // as we are doing %m res can always store <=10^9+6 values
    while(n) {
        if (n&1)
            res = (res * a * 1LL)%m;  // res * a may exceed 10^9(int range) so make them multiply by 1LL
        a = (a * a * 1LL) % m;   // so temporary result of a*a*1LL will be stored in long long buffer
        n >>= 1;                 // and doing %m will get answer into int range
    }
    cout << res << endl;
    // if a <= 10^18 then do initially  a = a%m;
    // if m <= 10^18 then a = 10^9 * 10^9 valid now a = 10^18 again a = 10^18 * 10^18 which cannot be stored in LL
    
}
