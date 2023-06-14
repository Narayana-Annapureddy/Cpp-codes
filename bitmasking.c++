#include<bits/stdc++.h>
using namespace std;

// Turn off last set bit  n & (n-1);
// For toggle use  ( n ^ (1 << i)) then it will toggle index i in number n
// bitmask = bit+mask (mask with bit to represent something)

void printIntInBin() {
    int n = 10;  // 31 to 0
    for(int i=31; i>=0; i--) {
        // check if ith bit is set or not
        cout << ( (n >> i) & 1 ) << " ";   // shift by i bits right side and check if last bit is 1 or 0
        // also it check if ith bit is set or not
    }
}

// Given an array we need to find the pairs whose bitwise & is greater than xor operation
void bitwiseANDGreaterThanXOR() {

    vector<int> a = {6, 2, 5, 3};   //   2:  0 0 0 0 ..... 0 0 1 0
    long long count = 0;           //    6:  0 0 0 0 ..... 0 1 1 0   ( stored in that way total of 32 bits )

    // 1 ^ 0  = 1  ,   1 ^ 1 = 0 ,   1 & 1 = 0  so find pairs who has 1 and 1 in the front like 6 and 5, 2 and 3
    // so there should not be (1, 0) initally for 2 and 6 it is (0, 1) in index 2 so xor is greater than & don't take it.

    vector<int> v(32);  
    for (int i=0; i<a.size(); i++) {

        // find the index of 1st set bit from left side 
        int val = v[i];
        for (int j=31; j>=0; j--)  {
            if (val >> j & 1)
                v[j] += 1;      // means at index j it is set bit for v[i]
        }
    }

    // so we have the count of numbers for which place they are set from left side
    for (int i=31; i>=0; i--) {

        // find no.of numbers which are set bit for index i and we can choose any two
        long long val = v[i];
        count += val * (val-1) / 2;
    }

    cout << count << endl;
}

// swap using xor operator
void swap(int a, int b) {
    a = a^b;
    b = a^b;  // (a^b^b i.e a)
    a = a^b;  // (a^b^a i.e b)
    cout << a << " " << b << endl;
}

// workers availability for 30 days will be given in a set. Need to assign a work to 2 people and they can do only 
// if both availabe in same day. find 2 workers who are best to work (find 2 workers who have max no.of common days)
// for intersection use bitWiseAnd operator and for union use bitWiseOr operator
void intersection() {
    int noOfWorkers;
    cin >> noOfWorkers;
    vector<int> masks;   // instead of 2d vector create vector masks of type int with available days.

    for(int i=0; i<noOfWorkers; i++)  {
        // read the input of ith worker availability days
        
        int noOfDaysAvailable,  mask = 0;  // mask represents the availabe days of employee
        cin >> noOfDaysAvailable;

        while(noOfDaysAvailable--) {
            int val;
            cin >> val;
            mask |= (1 << val);  // set the val number in mask
        }

        masks.push_back(mask);  // if availabe = [1, 9, 23, 30] then set the 1st, 9th, 23rd, 30th bits set in mask
    }
    // Now need to find the max value we get after applying bitwise AND between any two workers mask
    int answer = 0;    // store that max bitWise AND between any two workers
    for(int i=0; i<noOfWorkers; i++) {
        for(int j=i+1; j<noOfWorkers; j++) {
            int result = masks[i] & masks[j];
            // now find how many set bits are present in result
            int count = 0;
            while (result) {
                count++;
                result &= (result-1);   // switch off last set bit from left side
            }
            cout << i << " " << j << " " << count << endl;
            answer = max(answer, count);
        }
    }
    cout << answer;
}

// xor of all numbers from 1 to n (1^2^3^...n)
void xor_upto_n(int n) {
    // (n%4) == 0 then xor = n
    // (n%4) == 1 then xor = 1
    // (n%4) == 2 then xor = n+1
    // (n%4) == 3 then xor = 0
    
    // to xor in given range(L,R)
    // upto 1 to L and 1 to R we can get 
    // so it is (1 to R) ^ (1 to L-1) then we can get ( L^(L+1)^(L+2)...^R )
}

void even_or_odd(int n) {
    if (n&1 == 0)
        cout << "even" << endl;
    else
        cout << "odd" << endl;
}

// ith bit is set or not in number n (n,i)
bool i_set_or_not(int n, int i) {
    // create mask variable with 1 at ith position and 0 at remaining places.  1  1  0  1  0  1   (2nd pos)
    int mask = (1 << i);     // now do bitwise and (&) operation with num n    0  0  0  1  0  0   (mask)
    bool res = mask & n;                                                    // res is not 0
    return res != 0;
    // even it is best ( (n >> i) & 1 )  shift n by i bits and ith bit will be at end and check if last by set or not
}

// set ith bit
int set_i(int n, int i) {
    // create mask such that no change in remaining positions and put 1 in ith pos.
    // (0 | a) = a  so for remaining pos it is 0 and pos i it is 1         1 1 0 0 1 0 1  (3rd pos)
    int mask = (1 << i);     // now do bitwise or (|) operation with n     0 0 0 1 0 0 0
    return (mask | n);
}

void setLastIbits() {
    // ex: set upto 5th bit from last (0 to 5)  so bitOr with   000000111111   (6 set bits last)
    // we can get last 6 bits set if 2^7-1   ( 1 << (i+1)) - 1
    int n = 59, i=5;
    int mask = ( 1 << (i+1)) - 1;
    cout << (n | mask );
}

// unset ith bit i.e make it 0
int clear_i(int n, int i) {
    // create mask such that no change in remaining pos and put 0 in ith pos
    // (1 & a) = a   so put 1 in all pos except i and 0 in ith pos       1  1  0  1  0  1  (2nd pos)
    int mask = ~(1 << i);    // just do complement for 1 << i to get     1  1  1  0  1  1   (mask do & operation)
    return (mask & n);
}

// ******* remove last set bit i.e make it zero  **********
int remove_last_set(int n) {
    int mask = n-1;        // n is different from n-1 only at last set bit      14 :  1  1  1  0
    return n & (n-1);                                      //                   13 :  1  1  0  1
}

// find last set bit
int last_set_bit(int n) {
    int i;
    while((n&1)==0) {
        i++;
        n >>= 1;
    }
    return i;
}

// count the no.of set bits 
int count_set_bits(int n) {
    // The idea is remove all set bits one by one from last using remove_last_set concept
    int count = 0;
    while(n) {
        count++;
        n = n & (n-1);    // Turn off right most bit every time
    }
    return count;
}

// Two numbers are repeated once and all other are twice  [5,2,2,4,1,15,1] (5,7 are once)
void two_numbers_once(int *a, int n) {
    // two numbers differ by atleast one bit as they are different (5: 0 1 0 1   15: 1 1 1 1)  2nd bit differ
    // Now divide into two groups based on one is with 0 and the other is 1 at that differ pos.
    // so surely that two numbers go to different groups
    int xor_val = 0, last_differ_bit = 0, mask, n1=0, n2=0;
    for(int i=0; i<n; i++) {
        xor_val ^= a[i];
    }
    // find the last set bit          // (n = n & (n-1))
    while((xor_val & 1) == 0) {
        last_differ_bit++;
        xor_val >>= 1;
    }
    mask = (1 << last_differ_bit);
    for(int i=0; i<n; i++) {
        if (mask&a[i])
            n1 ^= a[i];
        else
            n2 ^= a[i];
    }
    cout << n1 << n2;
}

// generate all possible subsets using bit manipulation
void subset(vector <int> s) {
    int len = s.size();
    for(int i=0; i<(1<<len); i++) {  // 0 to (2^n)-1
        vector <int> ds;
        for(int j=0; j<len; j++) {
            if ( (1<<j & i) != 0 ) {    // means jth bit in number i is set so include in set.
                ds.emplace_back(s[j]);
            } 
        }
        for (auto it: ds)
            cout << it;
        cout << endl;
    }
}

// Create a ds set which store values x <= 63 and allow operations add, remove, print values
// it is used in dynamic programming i.e bit masking
void ds_set() {
    long long x = 0, n;
    // to add number n <= 63 set index n as 1 in binary rep of x (add(5) then set index 5)
    x | (1<<n);  // set index n 
    // to remove number n <= 63 then unset index n in bin rep of x (remove(5) then unset index 5)
    x & ~(1<<n);
    // to print the values in set
    for(int i=0; i<64; i++) {
        if (x & (1<<i))     // check whether ith index is set or not if it is set then it is in set ds
            cout << i << endl;
    }
}


int main() {
    
    intersection();
    return 0;
}
